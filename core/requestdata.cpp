#include "requestdata.h"
#include "core/serverdata.h"
#include "exception/qtexception.h"
#include <QStringList>
#include <QUrl>
#include "arrayrequestparam.h"
#include "stringkeyarrayparam.h"
#include "arrayvalue.h"
#include "stdint.h"
#include "util/file/fileutil.h"
#include <QBuffer>
#include "uploadedfile.h"
#include "uploadedfilearray.h"
#include "uploadedfilestringkeyarray.h"
#include <QDir>
#include <QFile>
#include <QDateTime>

#ifdef QT_DEBUG
#include <QDebug>
#endif

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



void RequestData::parseGetParams(const QUrl& url)
{
    QString requestString(url.query());
    if ( requestString.isEmpty()) {
        return;
    } else {
        QStringList parts = requestString.split(QChar('&'));

        for(const QString & part : parts) {
            int j;
            if ( (j=part.indexOf(QChar('=')))>-1) {
                addToHashtable(part.left(j),part.mid(j+1),getParams);
            }

        }
    }
}

int RequestData::checkNotEof(int c)
{
    if(c==-1)
        throw QtException("unexpected end of stream");
    return c;
}

void RequestData::expectChar(int c, int expected)
{
    if(c!=expected)
        throw QtException(QStringLiteral("expected character %1 but got %2").arg(static_cast<char>(expected),c));
}

void RequestData::parseMultipart(QIODevice *writeDevice,const FCGX_Request & request, bool & foundFinalDelimiter, const QString &delimiter)
{
    int c;

    char writeBuf[BUF_SIZE];
    int bufpos = 0;
    while((c=FCGX_GetChar(request.in))>-1) {
        //  writeFileBuf(&uploadedFile,bufpos,writeBuf,c);

        if(c == CR) {
            c=checkNotEof(FCGX_GetChar(request.in));
            if(c == NL) {
                QByteArray tempBuf;
                tempBuf.reserve(delimiter.length());
                bool foundDelimiter = true;
                for(int i=0;i<delimiter.size();i++) {
                    c = checkNotEof(FCGX_GetChar(request.in));
                    tempBuf.append(static_cast<char>(c));

                    if(c == 0 || delimiter[i] != c) {
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
                         throw QtException("unexpected character");
                     }

                } else {
                    writeFileBuf(writeDevice,bufpos,writeBuf,CR);
                    writeFileBuf(writeDevice,bufpos,writeBuf,NL);
                    for(int i=0;i<tempBuf.size(); i++) {
                        writeFileBuf(writeDevice,bufpos,writeBuf,tempBuf[i]);
                    }
                }
            } else {
                writeFileBuf(writeDevice,bufpos,writeBuf,CR);
                writeFileBuf(writeDevice,bufpos,writeBuf,c);
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
    QString contentLengthStr(FCGX_GetParam("CONTENT_LENGTH", request.envp));

    bool ok;
    uint32_t contentLength = contentLengthStr.toULong(&ok);
    if( contentType[0] == QLatin1Literal("multipart/form-data")) {
        int indexEq = contentType[1].indexOf('=');
        if(indexEq == -1) {
            throw QtException(QLatin1Literal("invalid data"));
        }
        QString delimiter = QStringLiteral("--%1").arg(contentType[1].mid(indexEq+1));
        if(!delimiter.startsWith(QLatin1Literal("--"))) {
            throw QtException(QLatin1Literal("invalid data"));
        }


        QChar quot('"');
        QString crlf("\r\n");
        char readBuf[BUF_SIZE];
        QString fieldName;
        QString line;

        if(FCGX_GetLine(readBuf,BUF_SIZE,request.in)!=nullptr) {
            line =  QString::fromUtf8(readBuf);
            if(line != delimiter+crlf) {
                throw QtException(QLatin1Literal("unexpected end of data: ") + line);
            }
        }

        //int r;
        while(FCGX_GetLine(readBuf,BUF_SIZE,request.in)!=nullptr) {
            line =  QString::fromUtf8(readBuf);
            QString fileName;
            QString mimeType;
            QString contentTransferEncoding;
            bool foundFinalDelimiter = false;

            while(line != crlf) {
                int k = line.indexOf(QChar(':'));
                QString header = line.left(k).toLower();
                QString headerValue = line.mid(k+1).trimmed();


                if(header == QLatin1Literal("content-disposition")) {
                    QStringList contentDispositionParts = headerValue.split(QChar(';'));
                    for(auto c : contentDispositionParts) {
                        QString trimmed = c.trimmed();
                        if(trimmed.startsWith(QLatin1Literal("name=\""))) {
                            int indexStart = trimmed.indexOf(quot,5)+1;
                            int indexEnd =trimmed.indexOf(quot,indexStart);
                            if(indexStart == -1 || indexEnd < indexStart) {
                                throw QtException(QLatin1Literal("invalid data"));
                            }
                            fieldName = trimmed.mid(trimmed.indexOf(quot)+1,indexEnd - indexStart );
                        } else if(trimmed.startsWith(QLatin1Literal("filename=\""))) {
                            int indexStart = trimmed.indexOf(quot,9)+1;
                            int indexEnd =trimmed.indexOf(quot,indexStart);
                            if(indexStart == -1 || indexEnd < indexStart) {
                                throw QtException(QLatin1Literal("invalid data"));
                            }
                            fileName = trimmed.mid(trimmed.indexOf(quot)+1,indexEnd - indexStart );
                            if(!FileUtil::isValidFileName(fieldName)) {
                                throw QtException(QLatin1Literal("invalid data"));
                            }
                        }
                    }
                } else if(header == QLatin1Literal("content-type")) {
                    mimeType = headerValue.trimmed();
                } else if(header == QLatin1Literal("content-transfer-encoding")) {
                    contentTransferEncoding = headerValue.trimmed();
                }

                if(FCGX_GetLine(readBuf,BUF_SIZE,request.in)!=nullptr) {
                    line =  QString::fromUtf8(readBuf);
                } else {
                    throw QtException(QLatin1Literal("unexpected end of data"));
                }
            }




            if(!fileName.isEmpty()) {
                QString filePath = QStringLiteral("%1/upload-%2-%3").arg(QDir::tempPath(), QString::number(QDateTime::currentMSecsSinceEpoch()),fileName);
                if(filePath.endsWith(QLatin1Literal(".exe"))
                        || filePath.endsWith(QLatin1Literal(".dll"))
                        ||filePath.endsWith(QLatin1Literal(".so"))
                        ||filePath.endsWith(QLatin1Literal(".dylib"))
                        ||filePath.endsWith(QLatin1Literal((".php")))) {
                    throw QtException("executable files are not allowed");
                }

                QFile uploadedFile( filePath );
                uploadedFile.open(QIODevice::WriteOnly|QIODevice::Truncate);
                parseMultipart(&uploadedFile,request,foundFinalDelimiter,delimiter);

                uploadedFile.close();



                if(fieldName.endsWith(QLatin1Literal("[]"))) {
                    int j = fieldName.indexOf('[');
                    if(j == -1) {
                        throw QtException(QLatin1Literal("Unexpected error"));
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
                                throw QtException(QLatin1Literal("Upload error"));
                            }
                        }
                    }
                    if(!found) {
                        uploadFiles.append(new UploadedFileArray(arrayBaseName,UploadedFile(fileName,arrayBaseName,filePath,mimeType,uploadedFile.size())));
                    }
                } else if(fieldName.endsWith(']')){
                    int j = fieldName.indexOf('[');
                    if(j == -1) {
                        throw QtException(QLatin1Literal("Unexpected error"));
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
                                throw QtException(QLatin1Literal("Upload error"));
                            }
                        }
                    }
                    if(!found) {
                        uploadFiles.append(new UploadedFileStringKeyArray(arrayBaseName,key,UploadedFile(fileName,arrayBaseName,filePath,mimeType,uploadedFile.size())));
                    }

                } else {
                    for(const auto u : uploadFiles) {
                        if(u->getFieldName() == fieldName) {
                            throw QtException(QLatin1Literal("Upload error"));
                        }
                    }
                    uploadFiles.append(new UploadedFile(fileName, fieldName,filePath,mimeType,uploadedFile.size()));
                }
            } else {
                QBuffer buffer;
                if(buffer.open(QIODevice::WriteOnly)){
                    parseMultipart(&buffer,request,foundFinalDelimiter,delimiter);
                    addToHashtable(fieldName,QString::fromUtf8(buffer.data()),postParams);
                    buffer.close();
                }

            }

            if(foundFinalDelimiter) {
                if (FCGX_GetChar(request.in) == -1) {
                    break;
                } else {
                    throw QtException(QLatin1Literal("Expected EOF"));
                }
            }

        }
    } else {

        if (!ok) {
            throw QtException(QLatin1Literal("Invalid content length"));
        } else {
            char * buf= new char[contentLength+1];


            QString paramStr = QString::fromUtf8(FCGX_GetLine(buf,static_cast<int>(contentLength)+1,request.in));
            auto list = paramStr.split(QChar('&'));

            QString requestString(paramStr.replace(QChar('+'),QLatin1Literal("%20")));
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

            delete[] buf;
        }


    }

}



void RequestData::addToHashtable(const QString &key, const QString &strValue, QHash<QString, AbstractRequestParam *> &params)
{
    StringKeyArrayParam* currentArray = nullptr;
    QString name;
    if (key.endsWith(QLatin1Literal("[]"))) {
        name = key.left(key.indexOf('['));
        ArrayRequestParam*arr = nullptr;
        if (params.contains(name)) {
            arr = dynamic_cast<ArrayRequestParam*>(params.value(name));
            if (arr == nullptr) {
                throw QtException(QLatin1Literal("Unexpected error"));
            }
        } else {
            arr = new ArrayRequestParam(name);
            params.insert(name, arr);
        }
        arr->append(strValue);
    } else if (key.endsWith(QChar(']'))) {
        int j = key.indexOf('[');
        if(j == -1) {
            throw QtException(QLatin1Literal("Unexpected error"));
        }
        name = key.left(j);
        if (params.contains(name)) {
            currentArray = dynamic_cast<StringKeyArrayParam*>(params.value(name));
            if (currentArray == nullptr) {
                throw QtException(QLatin1Literal("Unexpected error"));
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
                    if (currentArray->contains(arrayIndex)) {
                        currentArray = dynamic_cast<StringKeyArrayParam*>(currentArray->value(arrayIndex));
                        if (currentArray == nullptr) {
                            throw QtException(QLatin1Literal("Unexpected error"));
                        }
                    } else {
                        StringKeyArrayParam*dimension=new StringKeyArrayParam(name);
                        currentArray->insert(key.mid(arrayStart,arrayEnd-arrayStart),dimension);
                        currentArray = dimension;
                    }

                } else {
                    currentArray->insert(key.mid(arrayStart,arrayEnd-arrayStart),new ArrayValue(strValue));
                    currentArray = nullptr;
                }
            }
        }
    } else {
        params.insert(key, new RequestParam(key, strValue));
    }
}

void RequestData::writeFileBuf(QIODevice *writeDevice, int &pos, char *buf, char c)
{
    buf[pos++] = c;
    if(pos == BUF_SIZE) {
        writeDevice->write(buf, BUF_SIZE);
        pos = 0;
    }
}

void RequestData::writeFileBuf(QIODevice * writeDevice, int &pos, char *buf, int c)
{
    buf[pos++] = static_cast<char>(c);
    if(pos == BUF_SIZE) {
        writeDevice->write(buf, BUF_SIZE);
        pos = 0;
    }
}

const QString & RequestData::getString(const QString & name) const
{
    if (getParams.contains(name)) {
        RequestParam * p = dynamic_cast< RequestParam* >(getParams.value(name));
        if (p == nullptr) {
            throw QtException(QLatin1Literal("Parameter is not a simple value"));
        }
        return p->getValue();
    } else {
        throw QtException(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}

const QString & RequestData::postString(const QString &name) const
{
    if (postParams.contains(name)) {
        RequestParam * p = dynamic_cast< RequestParam* >(postParams.value(name));
        if (p == nullptr) {
            throw QtException(QLatin1Literal("Parameter is not a simple value"));
        }
        return p->getValue();
    } else {
        throw QtException(QStringLiteral("Parameter %1 does not exist").arg(name));
    }
}

int RequestData::getInt(const QString & name) const
{
    bool ok = false;
    int i = getString(name).toInt(&ok);
    if (!ok) throw QtException(QLatin1Literal("Parameter is not a number"));
    return i;
}

qint64 RequestData::getInt64(const QString &name) const
{
    QString value(getString(name));
    bool ok = false;
    qint64 i = value.toLongLong(&ok);
    if (!ok) throw QtException(QLatin1Literal("Parameter is not a number"));
    return i;
}

int RequestData::postInt(const QString & name) const
{
    bool ok = false;
    int i = postString(name).toInt(&ok);
    if (!ok) throw QtException(QLatin1Literal("Parameter is not a number"));
    return i;
}

qint64 RequestData::postInt64(const QString &name) const
{
    bool ok = false;
    qint64 i = postString(name).toLongLong(&ok);
    if (!ok) throw QtException(QLatin1Literal("Parameter is not a number"));
    return i;
}

double RequestData::postDouble(const QString &name) const
{
    QString value(postString(name));
    bool ok = false;
    double d = value.replace(QChar(','),QChar('.')).toDouble(&ok);
    if (!ok) throw QtException(QLatin1Literal("Parameter is not a number"));
    return d;
}

double RequestData::getDouble(const QString &name) const
{
    QString value(getString(name));
    bool ok = false;
    double d = value.replace(QChar(','),QChar('.')).toDouble(&ok);
    if (!ok) throw QtException(QLatin1Literal("Parameter is not a number"));
    return d;
}

bool RequestData::postBool(const QString &name) const
{
    QString value(postString(name));
    return value == QLatin1Literal("1") || value == QLatin1Literal("true");
}

 const ArrayRequestParam & RequestData::getArray(const QString &name) const
{
    if (getParams.contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(getParams.value(name));
        if (p == nullptr) {
            throw QtException(QLatin1Literal("Parameter is not an array"));
        }
        return *p;
    } else {
        throw QtException(QLatin1Literal("Parameter does not exist"));
    }
}

const StringKeyArrayParam &RequestData::getStringKeyArray(const QString &name) const
{
    if (getParams.contains(name)) {
        StringKeyArrayParam * p = dynamic_cast< StringKeyArrayParam* >(postParams.value(name));
        if (p == nullptr) {
            throw QtException(QLatin1Literal("Parameter is not an array"));
        }
        return *p;
    } else {
        throw QtException(QLatin1Literal("Parameter does not exist"));
    }
}


const ArrayRequestParam &RequestData::postArray(const QString &name) const
{
    if (postParams.contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(postParams.value(name));
        if (p == nullptr) {
            throw QtException(QLatin1Literal("Parameter is not an array"));
        }
        return *p;
    } else {
        throw QtException(QLatin1Literal("Parameter does not exist"));
    }
}

const StringKeyArrayParam & RequestData::postStringKeyArray(const QString &name) const
{
    if (postParams.contains(name)) {
        StringKeyArrayParam * p = dynamic_cast< StringKeyArrayParam* >(postParams.value(name));
        if (p == nullptr) {
            throw QtException(QLatin1Literal("Parameter is not an array"));
        }
        return *p;
    } else {
        throw QtException(QLatin1Literal("Parameter does not exist"));
    }
}


QString RequestData::getArrayValueString(const QString &name, const QString &key) const
{
    if (getParams.contains(name)) {
        AbstractStringKeyArrayParam * p = dynamic_cast< AbstractStringKeyArrayParam* >(getParams.value(name));
        if (p == nullptr) {
            throw QtException(QLatin1Literal("Parameter is not an array"));
        }
        ArrayValue * v = dynamic_cast<ArrayValue*>(p->val(key));
        if(v == nullptr) {
            throw QtException(QStringLiteral("Array key %1 does not exists").arg(key));
        }

        return  v->getValue();
    } else {
        throw QtException(QLatin1Literal("Parameter does not exist"));
    }
}

QString RequestData::getArrayValueString(const QString &name, int index) const
{
    if (getParams.contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(getParams.value(name));
        if (p == nullptr) {
            throw QtException(QLatin1Literal("Parameter is not an array"));
        }
        if(index >= 0 && index < p->size()) {
            return p->at(index);
        } else {
            throw QtException(QStringLiteral("Array index %1 does not exists").arg(index));
        }


    } else {
        throw QtException(QLatin1Literal("Parameter does not exist"));
    }
}

int RequestData::getArrayValueInt(const QString &name, const QString &key) const
{
    QString value(getArrayValueString(name,key));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throw QtException(QLatin1Literal("Parameter is not a number"));
    return i;
}

int RequestData::getArrayValueInt(const QString &name, int index) const
{
    QString value(getArrayValueString(name,index));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throw QtException(QLatin1Literal("Parameter is not a number"));
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
                throw QtException(QLatin1Literal("Parameter is not a simple file field"));
            }
        }
    }
    throw QtException(QLatin1Literal("no such file"));

}

const UploadedFileArray & RequestData::uploadedFileArray(const QString &fieldname) const
{
    for(const auto u : this->uploadFiles) {
        if(u->getFieldName() == fieldname) {
            auto f = dynamic_cast<UploadedFileArray*>(u);
            if(f != nullptr) {
                return *f;
            } else {
                throw QtException(QLatin1Literal("Parameter is not an array file field"));
            }
        }
    }
    throw QtException(QLatin1Literal("no such file"));

}

const UploadedFileStringKeyArray & RequestData::uploadedFileArrayStringKey(const QString &fieldname) const
{
    for(const auto u : this->uploadFiles) {
        if(u->getFieldName() == fieldname) {
            auto f = dynamic_cast<UploadedFileStringKeyArray*>(u);
            if(f != nullptr) {
                return *f;
            } else {
                throw QtException(QLatin1Literal("Parameter is not an array file field"));
            }
        }
    }
    throw QtException(QLatin1Literal("no such file"));
}

QVector<int> RequestData::getIntArray(const QString &name) const
{
    auto data = RequestData::getArray(name);
    QVector<int> result;
    for(const auto & d : data) {
        bool ok = false;
        result << d.toInt(&ok);
        if(!ok) {
            throw QtException(QLatin1Literal("Parameter is not an integer"));
        }
    }
    return result;
}

QVector<int> RequestData::postIntArray(const QString &name) const
{
    auto data = RequestData::postArray(name);
    QVector<int> result;
    for(const auto & d : data) {
        bool ok = false;
        result << d.toInt(&ok);
        if(!ok) {
            throw QtException(QLatin1Literal("Parameter is not an integer"));
        }
    }
    return result;
}



