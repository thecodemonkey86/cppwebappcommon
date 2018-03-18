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

#ifdef QT_DEBUG
#include <QDebug>
#include <QFile>

#endif

using namespace QtCommon2;

RequestData::RequestData(const FCGX_Request & request, const QUrl &url)
{

    parseCookies(request);
    parseGetParams(url);
    if (strcmp(FCGX_GetParam("REQUEST_METHOD", request.envp),"POST" )==0) {
        parsePostParams(request);
    }
}

RequestData::~RequestData()
{
    qDeleteAll(getParams.begin(),getParams.end());
    qDeleteAll(postParams.begin(),postParams.end());
}

/**
 * @brief RequestData::parseParams
 * @param requestString urldecoded
 * @param params destination
 */
void RequestData::parseParams(const QString&requestString, QHash<QString, AbstractRequestParam *> &params)
{
    if ( requestString.isEmpty()) {
        return;
    } else {
        QStringList parts = requestString.split(QChar('&'));

        for(const QString & part : parts) {
            int j;
            if ( (j=part.indexOf(QChar('=')))>-1) {
                QString key(part.left(j));
                QString strValue( part.mid(j+1));
                parseParam(key,strValue,params);
            }

        }
    }
}

void RequestData::parseGetParams(const QUrl& url)
{
    parseParams(url.query(),getParams);
}

void RequestData::parsePostParams(const FCGX_Request & request)
{
    QStringList contentType = QString(FCGX_GetParam("CONTENT_TYPE", request.envp)).split(QChar(';'));
    QString contentLengthStr(FCGX_GetParam("CONTENT_LENGTH", request.envp));

    bool ok;
    int64_t contentLength = contentLengthStr.toULongLong(&ok);
    if( contentType[0] == QStringLiteral("multipart/form-data")) {
        int indexEq = contentType[1].indexOf('=');
        if(indexEq == -1) {
            throw QtException(QStringLiteral("invalid data"));
        }
        QString delimiter = QStringLiteral("--%1\r\n").arg(contentType[1].mid(indexEq+1));
        if(!delimiter.startsWith(QStringLiteral("--"))) {
            throw QtException(QStringLiteral("invalid data"));
        }


        QChar quot('"');
        char * buf = new char[BUF_SIZE];
        QString fieldName;
        QString line;

        if(FCGX_GetLine(buf,BUF_SIZE,request.in)!=nullptr) {
            line =  QString::fromLatin1(buf);
            if(line != delimiter) {
                throw QtException(QStringLiteral("unexpected end of data: ") + line);
            }
        }

        //int r;
        while(FCGX_GetLine(buf,BUF_SIZE,request.in)!=nullptr) {
            line =  QString::fromLatin1(buf);
            QString fileName;
            QString mimeType;

            while(line != QStringLiteral("\r\n")) {
                int k = line.indexOf(QChar(':'));
                QString header = line.left(k).toLower();
                QString headerValue = line.mid(k+1).trimmed();


                if(header == QStringLiteral("content-disposition")) {
                    QStringList contentDispositionParts = headerValue.split(QChar(';'));
                    for(auto c : contentDispositionParts) {
                        QString trimmed = c.trimmed();
                        if(trimmed.startsWith(QStringLiteral("name=\""))) {
                            int indexStart = trimmed.indexOf(quot,5)+1;
                            int indexEnd =trimmed.indexOf(quot,indexStart);
                            if(indexStart == -1 || indexEnd < indexStart) {
                                throw QtException(QStringLiteral("invalid data"));
                            }
                            fieldName = trimmed.mid(trimmed.indexOf(quot)+1,indexEnd - indexStart );
                        } else if(trimmed.startsWith(QStringLiteral("filename=\""))) {
                            int indexStart = trimmed.indexOf(quot,9)+1;
                            int indexEnd =trimmed.indexOf(quot,indexStart);
                            if(indexStart == -1 || indexEnd < indexStart) {
                                throw QtException(QStringLiteral("invalid data"));
                            }
                            fileName = trimmed.mid(trimmed.indexOf(quot)+1,indexEnd - indexStart );
                            if(!FileUtil::isValidFileName(fieldName)) {
                                throw QtException(QStringLiteral("invalid data"));
                            }
                        }
                    }
                } else if(header == QStringLiteral("content-type")) {
                    mimeType = headerValue.trimmed();
                }

                if(FCGX_GetLine(buf,BUF_SIZE,request.in)!=nullptr) {
                    line =  QString::fromLatin1(buf);
                } else {
                    throw QtException(QStringLiteral("unexpected end of data"));
                }
            }




            if(!fileName.isEmpty()) {
                QFile uploadedFile( QStringLiteral("/tmp/upload-")+fileName);
                uploadedFile.open(QIODevice::WriteOnly|QIODevice::Truncate);
                int c;
                QByteArray byteArray;
                byteArray.reserve(BUF_SIZE);
                char * writeBuf = new char[BUF_SIZE];
                int bufpos = 0;
                while((c=FCGX_GetChar(request.in))>-1) {
                  //  writeFileBuf(&uploadedFile,bufpos,writeBuf,c);

                    if(c == CR) {
                        c=FCGX_GetChar(request.in);
                        if(c == NL) {
                            QByteArray tempBuf;
                            tempBuf.reserve(32);
                            bool foundDelimiter = true;
                            for(int i=0;i<delimiter.size();i++) {
                                int c = FCGX_GetChar(request.in);
                                tempBuf.append(c);
                                if(c == 0 || delimiter[i] != c) {
                                    foundDelimiter = false;
                                    break;
                                }
                            }
                            if(foundDelimiter) {
                                break;
                            } else {
                                writeFileBuf(&uploadedFile,bufpos,writeBuf,CR);
                                writeFileBuf(&uploadedFile,bufpos,writeBuf,NL);
                                for(int i=0;i<tempBuf.size(); i++) {
                                    writeFileBuf(&uploadedFile,bufpos,writeBuf,tempBuf[i]);
                                }
                            }
                        } else {
                            writeFileBuf(&uploadedFile,bufpos,writeBuf,CR);
                            writeFileBuf(&uploadedFile,bufpos,writeBuf,c);
                        }
                    } else {
                        writeFileBuf(&uploadedFile,bufpos,writeBuf,c);
                    }
                }
                uploadedFile.write(writeBuf,bufpos);
                uploadedFile.close();

            } else {
                if(FCGX_GetLine(buf,BUF_SIZE,request.in) != nullptr) {
                    QString value(buf);
                     parseParam(fieldName,value.trimmed(),postParams);
                    if(FCGX_GetLine(buf,BUF_SIZE,request.in) != nullptr) {
                        QString currentDelimiterEnd( buf);
                        if(delimiter == currentDelimiterEnd) {
                            qDebug() << "ok";
                        } else if(currentDelimiterEnd == QStringLiteral("%1--\r\n").arg(delimiter.mid(0,delimiter.length()-2))) {
                            break;
                        }
                    }
                }
            }



        }
        delete[] buf;
    } else {

        if (!ok) {
            throw QtException(QStringLiteral("Invalid content length"));
        } else {
            char * buf= new char[contentLength];


            QByteArray paramStr(FCGX_GetLine(buf,contentLength,request.in));
            parseParams(QUrl::fromPercentEncoding(paramStr),postParams);

            delete[] buf;
        }


    }

}

void RequestData::parseCookies(const FCGX_Request & request)
{
    //    cookies = new QHash<QString,QString>();
    QString cookieStr(FCGX_GetParam("HTTP_COOKIE", request.envp));
    if (cookieStr.trimmed().length()>0) {
        QStringList cookieStrLst =cookieStr.split(QChar(';'));
        for (const QString & s : cookieStrLst) {
            QStringList parts = s.split(QChar('='));
            if (parts.length()==2) {
                RequestData::cookies.insert(parts.at(0).trimmed(),parts.at(1).trimmed());
            } else {
                throw QtException(QStringLiteral("invalid cookie"));
            }
        }
    }
}

void RequestData::parseParam(const QString &key, const QString &strValue, QHash<QString, AbstractRequestParam *> &params)
{
    StringKeyArrayParam* currentArray = nullptr;
    QString name;
    if (key.endsWith(QStringLiteral("[]"))) {
        name = key.left(key.indexOf('['));
        ArrayRequestParam*arr = nullptr;
        if (params.contains(name)) {
            arr = dynamic_cast<ArrayRequestParam*>(params.value(name));
            if (arr == nullptr) {
                throw QtException(QStringLiteral("Unexpected error"));
            }
        } else {
            arr = new ArrayRequestParam(name);
            params.insert(name, arr);
        }
        arr->append(strValue);
    } else if (key.endsWith(QChar(']'))) {
        name = key.left(key.indexOf('['));
        if (params.contains(name)) {
            currentArray = dynamic_cast<StringKeyArrayParam*>(params.value(name));
            if (currentArray == nullptr) {
                throw QtException(QStringLiteral("Unexpected error"));
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
                            throw QtException(QStringLiteral("Unexpected error"));
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
        params.insert(key, new RequestParam<QString>(key, strValue));
    }
}

void RequestData::writeFileBuf(QFile *file, int &pos, char *&buf, char c)
{
    buf[pos++] = c;
    if(pos == BUF_SIZE) {
        file->write(buf, BUF_SIZE);
        pos = 0;
    }
}



QString RequestData::getString(const QString & name) const
{
    if (getParams.contains(name)) {
        RequestParam<QString> * p = dynamic_cast< RequestParam<QString>* >(getParams.value(name));
        if (p == nullptr) {
            throw QtException(QStringLiteral("Parameter is not a simple value"));
        }
        return p->getValue();
    } else {
        throw QtException(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}

QString RequestData::postString(const QString &name, bool required) const
{
    if (postParams.contains(name)) {
        RequestParam<QString> * p = dynamic_cast< RequestParam<QString>* >(postParams.value(name));
        if (p == nullptr) {
            throw QtException(QStringLiteral("Parameter is not a simple value"));
        }
        return p->getValue();
    } else if (required){
        throw QtException(QStringLiteral("Parameter %1 does not exist").arg(name));
    } else {
        return QStringLiteral("");
    }
}

int RequestData::getInt(const QString & name) const
{
    QString value(getString(name));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throw QtException(QStringLiteral("Parameter is not a number"));
    return i;
}

int RequestData::postInt(const QString & name) const
{
    QString value(postString(name));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throw QtException(QStringLiteral("Parameter is not a number"));
    return i;
}

double RequestData::postDouble(const QString &name) const
{
    QString value(postString(name));
    bool ok = false;
    double d = value.replace(QChar(','),QChar('.')).toDouble(&ok);
    if (!ok) throw QtException(QStringLiteral("Parameter is not a number"));
    return d;
}

double RequestData::getDouble(const QString &name) const
{
    QString value(getString(name));
    bool ok = false;
    double d = value.replace(QChar(','),QChar('.')).toDouble(&ok);
    if (!ok) throw QtException(QStringLiteral("Parameter is not a number"));
    return d;
}

bool RequestData::postBool(const QString &name) const
{
    QString value(postString(name));
    return value == QStringLiteral("1") || value == QStringLiteral("true");
}

ArrayRequestParam *RequestData::getArray(const QString &name) const
{
    if (getParams.contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(getParams.value(name));
        if (p == nullptr) {
            throw QtException(QStringLiteral("Parameter is not an array"));
        }
        return p;
    } else {
        throw QtException(QStringLiteral("Parameter does not exist"));
    }
}

bool RequestData::isGetParamSet(const QString &name) const
{
    return getParams.contains(name);
}

bool RequestData::isPostParamSet(const QString &name) const
{
    return postParams.contains(name);
}

QString RequestData::cookieString(const QString &name) const
{
    if(cookies.contains(name)) {
        return cookies[name];
    }
    throw QtException(QStringLiteral("Cookie is not set"));
}

QStringList RequestData::cookieAsArray(const QString &name) const
{
    return cookieString(name).split(QChar('|'));
}

bool RequestData::isCookieSet(const QString &name) const
{
    return cookies.contains(name);
}

