#include "requestdata.h"
#include "exception/qtexception.h"
#include <QStringList>
#include <QUrl>
#include "arrayrequestparam.h"
#include "qtypes.h"
#include "stringkeyarrayparam.h"
#include "arrayvalue.h"
#include "util/file/fileutil.h"
#include <QBuffer>
#include "uploadedfile.h"
#include "uploadedfilearray.h"
#include "uploadedfilestringkeyarray.h"
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QStack>
#include <QQueue>
#include <QSet>
#include "fcgiapp.h"
#include <QDebug>
#include <limits>

using namespace QtCommon2;

RequestData::RequestData(const FCGX_Request & request, const QUrl &url)
{

    parseGetParams(url);
    if (strcmp(FCGX_GetParam("REQUEST_METHOD", request.envp),"POST" )==0) {
        parsePostParams(request);
    }

}

RequestData::~RequestData()
{
    qDeleteAll(getParams.begin(),getParams.end());
    qDeleteAll(postParams.begin(),postParams.end());

    for(const auto & u : uploadFiles)
    {
        u->cleanup();
    }

    qDeleteAll(uploadFiles.begin(),uploadFiles.end());
}

void RequestData::setMaxPostSize(int newMaxPostSize)
{
    maxPostSize = newMaxPostSize;
}

void RequestData::parseGetParams(const QUrl &url)
{
    if ( !url.hasQuery()) {
        return;
    } else {
        QStringList parts = url.query().split(QChar('&'));

        for(const QString & part : parts) {
            int j;
            if ( (j=part.indexOf(QChar('=')))>-1) {
              addToHashtable(QUrl::fromPercentEncoding(part.left(j).toUtf8()),QUrl::fromPercentEncoding(part.mid(j+1).toUtf8()),getParams);
            }

        }
    }
}





void RequestData::parseMultipart(QIODevice *writeDevice,const FCGX_Request & request, bool & foundFinalDelimiter, const QString &delimiter)
{
    int c;
	QQueue<int> lookBehindBuffer;
    char writeBuf[BUF_SIZE];
    int bufpos = 0;
    while((c=(lookBehindBuffer.isEmpty() ? FCGX_GetChar(request.in) : lookBehindBuffer.dequeue() ))>-1) {
        
        if(c == CR) {

            c=checkNotEof((lookBehindBuffer.isEmpty() ? FCGX_GetChar(request.in) : lookBehindBuffer.dequeue() ));
            
            lookBehindBuffer.enqueue(c);
          
            if(c == NL) {
                bool foundDelimiter = true;

                for(int i=0;i<delimiter.size();i++) {

                    c = checkNotEof(FCGX_GetChar(request.in));
                    lookBehindBuffer.enqueue(c);
                    //qDebug() << static_cast<char>(c);
                    if(c == 0 || delimiter[i].toLatin1() != static_cast<char>(c)) {
                        foundDelimiter = false;
                        break;
                    }

                }
                if(foundDelimiter) {
                    c=checkNotEof(FCGX_GetChar(request.in));
                    if(c == CR){
                        expectChar(checkNotEof(FCGX_GetChar(request.in)), NL);
                        break;
                    } else if(c == HYPHEN) {
                        expectChar(checkNotEof(FCGX_GetChar(request.in)), HYPHEN);
                        expectChar(checkNotEof(FCGX_GetChar(request.in)), CR);
                        expectChar(checkNotEof(FCGX_GetChar(request.in)), NL);
                        foundFinalDelimiter = true;
                        break;
                    } else {
                        throwExceptionWithLine("unexpected character");
                    }

                } else {
                    writeFileBuf(writeDevice,bufpos,writeBuf,CR);
                }
            } else {
                 writeFileBuf(writeDevice,bufpos,writeBuf,CR);                 
            }
        } else {
            writeFileBuf(writeDevice,bufpos,writeBuf,c);
        }
    }
    if(bufpos > 0)
    {
        writeDevice->write(writeBuf,bufpos);
    }


}

void RequestData::parsePostParams(const FCGX_Request & request)
{
    QStringList contentType = QString(FCGX_GetParam("CONTENT_TYPE", request.envp)).split(QChar(';'));
    if(contentType.isEmpty())
    {
        throwExceptionWithLine(QStringLiteral("invalid content type"));
    }
    QString contentLengthStr(FCGX_GetParam("CONTENT_LENGTH", request.envp));

    bool ok;
    uint64_t contentLength = contentLengthStr.toULongLong(&ok);
    if( contentType[0] == "multipart/form-data") {
        if(contentType.size() < 2)
        {
            throwExceptionWithLine(QStringLiteral("invalid content type"));
        }
        int indexEq = contentType[1].indexOf('=');
        if(indexEq == -1) {
            throwExceptionWithLine(QStringLiteral("invalid data"));
        }
        QString delimiter = QStringLiteral("--%1").arg(contentType[1].mid(indexEq+1));
        if(!delimiter.startsWith(QStringLiteral("--"))) {
            throwExceptionWithLine(QStringLiteral("invalid data"));
        }


        QChar quot('"');
        QString crlf("\r\n");
        char readBuf[BUF_SIZE];
        QString fieldName;
        QString line;

        if(FCGX_GetLine(readBuf,BUF_SIZE,request.in)!=nullptr) {
            line =  QString::fromUtf8(readBuf);
            if(line != delimiter+crlf) {
                throwExceptionWithLine(QStringLiteral("unexpected end of data: ") + line);
            }
        }



        bool foundFinalDelimiter = false;
        while(!foundFinalDelimiter) {
            QString fileName;
            QString mimeType;
          //  QString contentTransferEncoding;

            bool eof=true;
            while(FCGX_GetLine(readBuf,BUF_SIZE,request.in)!=nullptr){
                eof = false;
                line =  QString::fromUtf8(readBuf);
                if(line == crlf){
                    break;
                }
                int k = line.indexOf(QChar(':'));
                QString header = line.left(k).toLower();
                QString headerValue = line.mid(k+1).trimmed();


                if(header == "content-disposition") {
                    qsizetype contentDispositionStart=0;
                    qsizetype i=0;
                    while(i < headerValue.size() - 1)
                    {
                        switch (headerValue[i].unicode()) {
                        case u'=':
                        {
                            QString key=headerValue.mid(contentDispositionStart,i-contentDispositionStart).trimmed();
                            if(headerValue[++i]==quot)
                            {
                                ++i;
                                contentDispositionStart=i;
                                while(i < headerValue.size())
                                {
                                    if(headerValue[i]==quot)
                                    {
                                        if(key=="name")
                                        {
                                            fieldName = headerValue.mid(contentDispositionStart,i-contentDispositionStart);
                                        } else if(key=="filename")
                                        {
                                            fileName = headerValue.mid(contentDispositionStart,i-contentDispositionStart);
                                        }
                                        break;
                                    }
                                    ++i;
                                }
                            }
                            else
                            {
                                throwExceptionWithLine("expected quote character");
                            }
                            break;
                        }
                        case u';':
                        {
                            contentDispositionStart = i+1;
                            break;
                        }
                        }

                        ++i;
                    }

                } else if(header == "content-type") {
                    mimeType = headerValue.trimmed();
                } /*else if(header == "content-transfer-encoding") {
                    contentTransferEncoding = headerValue.trimmed();
                }*/


            }

            if(eof)
            {
                throwExceptionWithLine("unexpected end of stream");
            }



            if(!fileName.isEmpty()) {
                if(!FileUtil::isValidFileName(fileName)) {
                    throwExceptionWithLine(QStringLiteral("invalid data"));
                }
                QString filePath = QStringLiteral("%1/upload-%2-%3").arg(QDir::tempPath(), QString::number(QDateTime::currentMSecsSinceEpoch()),fileName);
                if(filePath.endsWith(QStringLiteral(".exe"))
                        || filePath.endsWith(QStringLiteral(".dll"))
                        ||filePath.endsWith(QStringLiteral(".so"))
                        ||filePath.endsWith(QStringLiteral(".dylib"))
                        ||filePath.endsWith(QStringLiteral(".php"))) {
                    throwExceptionWithLine("executable files are not allowed");
                }

                QFile uploadedFile( filePath );
                uploadedFile.open(QIODevice::WriteOnly|QIODevice::Truncate);
                parseMultipart(&uploadedFile,request,foundFinalDelimiter,delimiter);

                uploadedFile.close();



                if(fieldName.endsWith(QStringLiteral("[]"))) {
                    int j = fieldName.indexOf('[');
                    if(j == -1) {
                        throwExceptionWithLine(QStringLiteral("Unexpected error"));
                    }
                    QString arrayBaseName = fieldName.left(j);
                    bool found = false;
                    for(const auto u : uploadFiles) {
                        if(u->getFieldName() == arrayBaseName) {
                            auto arr = dynamic_cast<UploadedFileArray*>(u);

                            if(arr != nullptr) {
                                arr->append(UploadedFile(fileName,arrayBaseName,filePath,mimeType,uploadedFile.size()));
                                found = true;
                                break;
                            } else {
                                throwExceptionWithLine(QStringLiteral("Upload error"));
                            }
                        }
                    }
                    if(!found) {
                        uploadFiles.append(new UploadedFileArray(arrayBaseName,UploadedFile(fileName,arrayBaseName,filePath,mimeType,uploadedFile.size())));
                    }
                } else if(fieldName.endsWith(']')){
                    int j = fieldName.indexOf('[');
                    if(j == -1) {
                        throwExceptionWithLine(QStringLiteral("Unexpected error"));
                    }
                    auto key = fieldName.mid(j+1,fieldName.length()-j-2);
                    QString arrayBaseName = fieldName.left(j);
                    bool found = false;
                    for(const auto u  : uploadFiles) {
                        if(u->getFieldName() == arrayBaseName) {
                            auto arr = dynamic_cast<UploadedFileStringKeyArray*>(u);

                            if(arr != nullptr) {
                                arr->insert(key, UploadedFile(fileName,arrayBaseName,filePath,mimeType,uploadedFile.size()));
                                found = true;
                            } else {
                                throwExceptionWithLine(QStringLiteral("Upload error"));
                            }
                        }
                    }
                    if(!found) {
                        uploadFiles.append(new UploadedFileStringKeyArray(arrayBaseName,key,UploadedFile(fileName,arrayBaseName,filePath,mimeType,uploadedFile.size())));
                    }

                } else {
                    for(const auto u : uploadFiles) {
                        if(u->getFieldName() == fieldName) {
                            throwExceptionWithLine(QStringLiteral("Upload error"));
                        }
                    }
                    uploadFiles.append(new UploadedFile(fileName, fieldName,filePath,mimeType,uploadedFile.size()));
                }
            } else {
                if(fieldName.isEmpty())
                {
                    throwExceptionWithLine("Invalid multipart. Field name is empty");
                }
                QBuffer buffer;
                if(buffer.open(QIODevice::WriteOnly)){
                    parseMultipart(&buffer,request,foundFinalDelimiter,delimiter);
                    addToHashtable(fieldName,QString::fromUtf8(buffer.data()),postParams);
                    buffer.close();
                }

            }


        }
        if (FCGX_GetChar(request.in) != -1) {
            throwExceptionWithLine(QStringLiteral("Expected EOF"));
        }
    } else {

        if (!ok) {
            throwExceptionWithLine(QStringLiteral("Invalid content length"));
        } else {
            if(contentLength>RequestData::maxPostSize) {
                throwExceptionWithLine(QStringLiteral("too large POST request"));
            }
            std::unique_ptr<char[]> buf(new char[contentLength+1]);


            //auto list = paramStr.split(QChar('&'));

            QString requestString(QString::fromUtf8(FCGX_GetLine(buf.get(),static_cast<int>(contentLength)+1,request.in)).replace(QChar('+'),QStringLiteral("%20")));
            if ( requestString.isEmpty()) {
                return;
            } else {
                QStringList parts = requestString.split(QChar('&'));

                for(const QString & part : parts) {
                    int j;
                    if ( (j=part.indexOf(QChar('=')))>-1) {
                        addToHashtable(QUrl::fromPercentEncoding(part.left(j).toUtf8()),QUrl::fromPercentEncoding(part.mid(j+1).toUtf8()),postParams);
                    }

                }
            }

        }


    }

}



void RequestData::addToHashtable(const QString &key, const QString &strValue, QHash<QString, AbstractRequestParam *> &params)
{
    StringKeyArrayParam* currentArray = nullptr;
    QString name;
    if (key.endsWith(QStringLiteral("[]"))) {
        name = key.left(key.indexOf('['));
        ArrayRequestParam*arr = nullptr;
        if (params.contains(name)) {
            arr = dynamic_cast<ArrayRequestParam*>(params.value(name));
            if (arr == nullptr) {
                throwExceptionWithLine(QStringLiteral("Unexpected error"));
            }
        } else {
            arr = new ArrayRequestParam(name);
            params.insert(name, arr);
        }
        arr->append(strValue);
    } else if (key.endsWith(QChar(']'))) {
        int j = key.indexOf('[');
        if(j == -1) {
            throwExceptionWithLine(QStringLiteral("Unexpected error"));
        }
        name = key.left(j);
        if (params.contains(name)) {
            currentArray = dynamic_cast<StringKeyArrayParam*>(params.value(name));
            if (currentArray == nullptr) {
                throwExceptionWithLine(QStringLiteral("Unexpected error"));
            }
        } else {
            currentArray = new StringKeyArrayParam(name);
            params.insert(name, currentArray);
        }
        int arrayStart = 0;
        int arrayEnd = 0;
        for(int i=0;i<key.length();i++) {
            if (key[i] == QChar('[')) {
                arrayStart = i+1;

            } else if (key[i] == QChar(']')) {
                arrayEnd = i;
                if (i < key.length()-1) {
                    QString arrayIndex(key.mid(arrayStart,arrayEnd-arrayStart));
                    if(currentArray==nullptr)
                    {
                        throwExceptionWithLine(QStringLiteral("Unexpected error"));
                    }
                    if (currentArray->contains(arrayIndex)) {
                        currentArray = dynamic_cast<StringKeyArrayParam*>(currentArray->value(arrayIndex));
                        if (currentArray == nullptr) {
                            throwExceptionWithLine(QStringLiteral("Unexpected error"));
                        }
                    } else {
                        StringKeyArrayParam*dimension=new StringKeyArrayParam(name);
                        currentArray->insert(key.mid(arrayStart,arrayEnd-arrayStart),dimension);
                        currentArray = dimension;
                    }

                } else {
                    if(currentArray==nullptr)
                    {
                        throwExceptionWithLine(QStringLiteral("Unexpected error"));
                    }
                    currentArray->insert(key.mid(arrayStart,arrayEnd-arrayStart),new ArrayValue(strValue));
                    currentArray = nullptr;
                }
            }
        }
    } else {
        params.insert(key, new RequestParam(key, strValue));
    }
}





const QString & RequestData::getString(const QString & name) const
{
    if (getParams.contains(name)) {
        RequestParam * p = dynamic_cast< RequestParam* >(getParams.value(name));
        if (p == nullptr) {
            throwExceptionWithLine(QStringLiteral("Parameter is not a simple value"));
        }
        return p->getValue();
    } else {
        throwExceptionWithLine(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}

const QString &RequestData::getStringNoCheckForExistance(const QString &name) const
{
  RequestParam * p = dynamic_cast< RequestParam* >(getParams.value(name));
  if (p == nullptr) {
    throwExceptionWithLine(QStringLiteral("Parameter is not a simple value"));
  }
  return p->getValue();
}

const QString & RequestData::postString(const QString &name) const
{
    if (postParams.contains(name)) {
        RequestParam * p = dynamic_cast< RequestParam* >(postParams.value(name));
        if (p == nullptr) {
            throwExceptionWithLine(QStringLiteral("Parameter is not a simple value"));
        }
        return p->getValue();
    } else {
        throwExceptionWithLine(QStringLiteral("Parameter %1 does not exist").arg(name));
    }
}

int RequestData::getInt(const QString & name) const
{
    bool ok = false;
    int i = getString(name).toInt(&ok);
    if (!ok) {
      qDebug()<< getString(name);
      throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
    }
    return i;
}

uint32_t RequestData::getUInt(const QString & name) const
{
  bool ok = false;
  uint32_t i = getString(name).toUInt(&ok);
  if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
  return i;
}

qint64 RequestData::getInt64(const QString &name) const
{
    QString value(getString(name));
    bool ok = false;
    qint64 i = value.toLongLong(&ok);
    if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
    return i;
}

int RequestData::postInt(const QString & name) const
{
    bool ok = false;
    int i = postString(name).toInt(&ok);
    if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number: ")+postString(name));
    return i;
}

uint32_t RequestData::postUInt(const QString & name) const
{
  bool ok = false;
  uint32_t i = postString(name).toUInt(&ok);
  if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
  return i;
}

qint64 RequestData::postInt64(const QString &name) const
{
    bool ok = false;
    qint64 i = postString(name).toLongLong(&ok);
    if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
    return i;
}

double RequestData::postDouble(const QString &name) const
{
    QString value(postString(name));
    bool ok = false;
    double d = value.replace(QChar(','),QChar('.')).toDouble(&ok);
    if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
    return d;
}

double RequestData::getDouble(const QString &name) const
{
    QString value(getString(name));
    bool ok = false;
    double d = value.replace(QChar(','),QChar('.')).toDouble(&ok);
    if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
    return d;
}

bool RequestData::getBool(const QString &name) const
{
  QString value(getString(name));
  return value == "1" || value == "true"|| value == "on";
}

bool RequestData::postBool(const QString &name) const
{
    QString value(postString(name));
    return value == "1" || value == "true" || value == "on";
}

ArrayRequestParam* RequestData::getArray(const QString &name) const
{
    if (getParams.contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(getParams.value(name));
        if (p == nullptr) {
            throwExceptionWithLine(QStringLiteral("Parameter is not an array"));
        }
        return p;
    } else {
        throwExceptionWithLine(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}

StringKeyArrayParam* RequestData::getStringKeyArray(const QString &name) const
{
    if (getParams.contains(name)) {
        StringKeyArrayParam * p = dynamic_cast< StringKeyArrayParam* >(getParams.value(name));
        if (p == nullptr) {
            throwExceptionWithLine(QStringLiteral("Parameter is not an array"));
        }
        return p;
    } else {
        throwExceptionWithLine(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}


ArrayRequestParam *RequestData::postArray(const QString &name) const
{
    if (postParams.contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(postParams.value(name));
        if (p == nullptr) {
            throwExceptionWithLine(QStringLiteral("Parameter is not an array"));
        }
        return p;
    } else {
        throwExceptionWithLine(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}

StringKeyArrayParam * RequestData::postStringKeyArray(const QString &name) const
{
    if (postParams.contains(name)) {
        StringKeyArrayParam * p = dynamic_cast< StringKeyArrayParam* >(postParams.value(name));
        if (p == nullptr) {
            throwExceptionWithLine(QStringLiteral("Parameter is not an array"));
        }
        return p;
    } else {
        throwExceptionWithLine(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}


QString RequestData::getArrayValueString(const QString &name, const QString &key) const
{
    if (getParams.contains(name)) {
        AbstractStringKeyArrayParam * p = dynamic_cast< AbstractStringKeyArrayParam* >(getParams.value(name));
        if (p == nullptr) {
            throwExceptionWithLine(QStringLiteral("Parameter is not an array"));
        }
        const ArrayValue * v = dynamic_cast<const ArrayValue*>(p->val(key));
        if(v == nullptr) {
            throwExceptionWithLine(QStringLiteral("Array key %1 does not exists").arg(key));
        }

        return  v->getValue();
    } else {
        throwExceptionWithLine(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}

QString RequestData::getArrayValueString(const QString &name, int index) const
{
    if (getParams.contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(getParams.value(name));
        if (p == nullptr) {
            throwExceptionWithLine(QStringLiteral("Parameter is not an array"));
        }
        if(index >= 0 && index < p->size()) {
            return p->at(index);
        } else {
            throwExceptionWithLine(QStringLiteral("Array index %1 does not exists").arg(index));
        }


    } else {
        throwExceptionWithLine(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}

int RequestData::getArrayCount(const QString &name) const
{
  return getArray(name)->size();
}

int RequestData::postArrayCount(const QString &name) const
{
  return postArray(name)->size();
}

int RequestData::getArrayValueInt(const QString &name, const QString &key) const
{
    QString value(getArrayValueString(name,key));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
    return i;
}

int RequestData::getArrayValueInt(const QString &name, int index) const
{
    QString value(getArrayValueString(name,index));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throwExceptionWithLine(QStringLiteral("Parameter is not a number"));
    return i;
}

bool RequestData::isGetParamSet(const QString &name) const
{
    return getParams.contains(name);
}

bool RequestData::isPostParamSet(const QString &name) const
{
    return postParams.contains(name);
}


QStringList RequestData::postFieldNames() const
{
    return postParams.keys();
}

const UploadedFile & RequestData::uploadedFile(const QString &fieldname) const
{
    for(const auto u : this->uploadFiles) {
        if(u->getFieldName() == fieldname) {
            auto f = dynamic_cast<UploadedFile*>(u);
            if(f != nullptr) {
                return *f;
            } else {
                throwExceptionWithLine(QStringLiteral("Parameter is not a simple file field"));
            }
        }
    }
    throwExceptionWithLine(QStringLiteral("no such file"));

}

const UploadedFileArray & RequestData::uploadedFileArray(const QString &fieldname) const
{
    for(const auto u : this->uploadFiles) {
        if(u->getFieldName() == fieldname) {
            auto f = dynamic_cast<UploadedFileArray*>(u);
            if(f != nullptr) {
                return *f;
            } else {
                throwExceptionWithLine(QStringLiteral("Parameter is not an array file field"));
            }
        }
    }
    throwExceptionWithLine(QStringLiteral("no such file"));

}

const UploadedFileStringKeyArray & RequestData::uploadedFileArrayStringKey(const QString &fieldname) const
{
    for(const auto u : this->uploadFiles) {
        if(u->getFieldName() == fieldname) {
            auto f = dynamic_cast<UploadedFileStringKeyArray*>(u);
            if(f != nullptr) {
                return *f;
            } else {
                throwExceptionWithLine(QStringLiteral("Parameter is not an array file field"));
            }
        }
    }
    throwExceptionWithLine(QStringLiteral("no such file"));
}

bool RequestData::isUploadedFileSet(const QString &fieldname) const
{
  for(const auto u : this->uploadFiles) {
    if(u->getFieldName() == fieldname) {
      return true;
    }
  }
  return false;
}

QVector<int> RequestData::getIntArray(const QString &name) const
{
    auto data = RequestData::getArray(name);
    QVector<int> result;
    for(const auto & d : *data) {
       if(!d.isEmpty()) {
        bool ok = false;
        result << d.toInt(&ok);
        if(!ok) {
            throwExceptionWithLine(QStringLiteral("Parameter is not an integer"));
        }
       }
    }
    return result;
}

QVector<int64_t> RequestData::getInt64Array(const QString &name) const
{
  auto data = RequestData::getArray(name);
  QVector<int64_t> result;
  for(const auto & d : *data) {
    if(!d.isEmpty()) {
      bool ok = false;
      result << d.toLongLong(&ok);
      if(!ok) {
        throwExceptionWithLine(QStringLiteral("Parameter is not an integer"));
      }
    }
  }
  return result;
}

QVector<int> RequestData::postIntArray(const QString &name) const
{
    auto data = RequestData::postArray(name);
    QVector<int> result;
    for(const auto & d : *data) {
      if(!d.isEmpty()) {
        bool ok = false;
        result << d.toInt(&ok);
        if(!ok) {
            throwExceptionWithLine(QStringLiteral("Parameter is not an integer"));
        }
      }
    }
    return result;
}

QVector<int64_t> RequestData::postInt64Array(const QString &name) const
{
  auto data = RequestData::postArray(name);
  QVector<int64_t> result;
  for(const auto & d : *data) {
    if(!d.isEmpty()) {
    bool ok = false;
    result << d.toInt(&ok);
    if(!ok) {
      throwExceptionWithLine(QStringLiteral("Parameter is not an integer"));
    }
    }
  }
  return result;
}

QStringList RequestData::getStringArray(const QString &name) const
{
  return static_cast<QStringList>(*getArray(name));
}

QStringList RequestData::postStringArray(const QString &name) const
{
  return static_cast<QStringList>(*postArray(name));
}

QSet<int64_t> RequestData::getInt64HashSet(const QString &name) const
{
  auto data = RequestData::getArray(name);
  QSet<int64_t>  result;
  for(const auto & d : *data) {
    bool ok = false;
    result << d.toInt(&ok);
    if(!ok) {
      throwExceptionWithLine(QStringLiteral("Parameter is not an integer"));
    }
  }
  return result;
}

QSet<int64_t> RequestData::postInt64HashSet(const QString &name) const
{
  auto data = RequestData::postArray(name);
  QSet<int64_t>  result;
  for(const auto & d : *data) {
    bool ok = false;
    result << d.toInt(&ok);
    if(!ok) {
      throwExceptionWithLine(QStringLiteral("Parameter is not an integer"));
    }
  }
  return result;
}

int RequestData::maxPostSize=std::numeric_limits<int>::max();
