#include "requestdata.h"
#include "core/serverdata.h"
#include "exception/qtexception.h"
#include <QStringList>
#include <QUrl>
#include "arrayrequestparam.h"
#include "stringkeyarrayparam.h"
#include "arrayvalue.h"
#include "stdint.h"
#include <QDebug>

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
//    delete getParams;
//    delete postParams;
//    delete cookies;
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
                if (key.endsWith(QString("[]"))) {
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
//        getParams = new QHash<QString,AbstractRequestParam*>();
    QString requestString = url.query();
    parseParams(requestString,getParams);


}

void RequestData::parsePostParams(const FCGX_Request & request)
{
    if (QString(FCGX_GetParam("REQUEST_METHOD", request.envp))==QString("POST")) {
//        if (postParams == nullptr) {
//             postParams = new QHash<QString,AbstractRequestParam*>();
//        } else {
//            postParams.clear();
//        }
        QString contentLengthStr(FCGX_GetParam("CONTENT_LENGTH", request.envp));
        qDebug()<<"Content-Length:"<<contentLengthStr;
        bool ok;
        int64_t contentLength = contentLengthStr.toULongLong(&ok);
        if (!ok) {
            throw QtException("Invalid content length");
        } else {
            const int bufSize = contentLength+1;
            char * buf= new char[bufSize];
            QString paramStr;
            qDebug()<<"before FCGX_GetStr";
           /* int r=0;
            while ( (r = FCGX_Get(buf, bufSize, request.in)>0)) {
                qDebug()<<r;
                paramStr+=QString::fromLocal8Bit(buf,r);
            }*/

            paramStr+=QString(FCGX_GetLine(buf,bufSize,request.in));

            //QString line(FCGX_GettLine(buf, contentLength, request.in));
            qDebug()<<"POST param: "<< paramStr;
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
foreach (QString s, cookieStrLst) {
    QStringList parts = s.split(QChar('='));
    if (parts.length()==2) {
        RequestData::cookies.insert(parts.at(0).trimmed(),parts.at(1).trimmed());
    } else {
        throw QtException("invalid cookie");
    }
}
}
}
QString RequestData::getString(const QString & name)
{
    if (getParams.contains(name)) {
        RequestParam<QString> * p = dynamic_cast< RequestParam<QString>* >(getParams.value(name));
        if (p == nullptr) {
            throw QtException("Parameter is not a simple value");
        }
        return p->getValue();
    } else {
        throw QtException(QStringLiteral("Parameter does not exist: %1").arg(name));
    }
}

QString RequestData::postString(const QString &name, bool required)
{
    if (postParams.contains(name)) {
        RequestParam<QString> * p = dynamic_cast< RequestParam<QString>* >(postParams.value(name));
        if (p == nullptr) {
            throw QtException("Parameter is not a simple value");
        }
        return p->getValue();
    } else if (required){
        throw QtException(QString("Parameter %1 does not exist").arg(name));
    } else {
        return QString("");
    }
}

int RequestData::getInt(const QString & name)
{
    QString value(getString(name));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throw QtException("Parameter is not a number");
    return i;
}

int RequestData::postInt(const QString & name)
{
    QString value(postString(name));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throw QtException("Parameter is not a number");
    return i;
}

double RequestData::postDouble(const QString &name)
{
    QString value(postString(name));
    bool ok = false;
    double d = value.replace(QChar(','),QChar('.')).toDouble(&ok);
    if (!ok) throw QtException("Parameter is not a number");
    return d;
}

double RequestData::getDouble(const QString &name)
{
    QString value(getString(name));
    bool ok = false;
    double d = value.replace(QChar(','),QChar('.')).toDouble(&ok);
    if (!ok) throw QtException("Parameter is not a number");
    return d;
}

bool RequestData::postBool(const QString &name)
{
    QString value(postString(name));
    return value == QString("1") || value == QString("true");
}

ArrayRequestParam *RequestData::getArray(const QString &name)
{
    if (getParams.contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(getParams.value(name));
        if (p == nullptr) {
            throw QtException("Parameter is not an array");
        }
        return p;
    } else {
        throw QtException("Parameter does not exist");
    }
}

bool RequestData::isGetParamSet(const QString &name)
{
    return getParams.contains(name);
}

bool RequestData::isPostParamSet(const QString &name)
{
    return postParams.contains(name);
}

QString RequestData::cookieString(const QString &name)
{
    if(cookies.contains(name)) {
        return cookies.value(name);
    }
    throw QtException("Cookie is not set");
}

QStringList RequestData::cookieAsArray(const QString &name)
{
    return cookieString(name).split("|");
}

bool RequestData::isCookieSet(const QString &name)
{
    return cookies.contains(name);
}

