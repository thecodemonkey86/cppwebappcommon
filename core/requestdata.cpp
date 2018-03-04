#include "requestdata.h"
#include "core/serverdata.h"
#include "exception/qtexception.h"
#include <QStringList>
#include <QUrl>
#include "arrayrequestparam.h"
#include "stringkeyarrayparam.h"
#include "arrayvalue.h"
#include "stdint.h"


#ifdef QT_DEBUG
    #include <QDebug>
    #include <QFile>

#endif

using namespace QtCommon2;

RequestData::RequestData(const FCGX_Request & request, const QUrl &url)
{

    parseCookies(request);
    parseGetParams(url);
    parsePostParams(request);
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
        StringKeyArrayParam* currentArray = nullptr;
        for(const QString & part : parts) {
            currentArray = nullptr;
            int j;
            if ( (j=part.indexOf(QChar('=')))>-1) {
                QString key(part.left(j));
                QString strValue( part.mid(j+1));
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

        }
    }
}

void RequestData::parseGetParams(const QUrl& url)
{
    parseParams(url.query(),getParams);
}

void RequestData::parsePostParams(const FCGX_Request & request)
{
    if (QString(FCGX_GetParam("REQUEST_METHOD", request.envp))==QStringLiteral("POST")) {

#ifdef QT_DEBUG
        QFile dbg("D:\\Temp\\debug.txt");
        dbg.open(QIODevice::WriteOnly|QIODevice::Truncate);
        dbg.write(FCGX_GetParam("CONTENT_TYPE", request.envp));
        dbg.close();
        return;
#endif

        QString contentLengthStr(FCGX_GetParam("CONTENT_LENGTH", request.envp));

        bool ok;
        int64_t contentLength = contentLengthStr.toULongLong(&ok);
        if (!ok) {
            throw QtException(QStringLiteral("Invalid content length"));
        } else {
            const int bufSize = contentLength+1;
            char * buf= new char[bufSize];
            QString paramStr;


            paramStr+=QString(FCGX_GetLine(buf,bufSize,request.in));

            parseParams(QUrl::fromPercentEncoding(paramStr.toUtf8()),postParams);
        }
    }


    //  char* line =    ;
    /*if ( line != nullptr ) {

    }*/
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

