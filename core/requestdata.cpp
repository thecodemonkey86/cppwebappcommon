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

RequestData::RequestData()
{

}

/**
 * @brief RequestData::parseParams
 * @param requestString urldecoded
 * @param params destination
 */
void RequestData::parseParams(const QString&requestString, QMap<QString, AbstractRequestParam *> *params)
{
    if ( requestString.isEmpty()) {
        return;
    } else {
        QStringList parts = requestString.split(QChar('&'));
        StringKeyArrayParam* currentArray = NULL;
        foreach (QString part, parts) {
            currentArray = NULL;
            int j;
            if ( (j=part.indexOf(QChar('=')))>-1) {
                QString key(part.left(j));
                QString strValue( part.mid(j+1));
                QString name;
                if (key.endsWith(QString("[]"))) {
                  name = key.left(key.indexOf('['));
                  ArrayRequestParam*arr = NULL;
                  if (params->contains(name)) {
                      arr = dynamic_cast<ArrayRequestParam*>(params->value(name));
                      if (arr == NULL) {
                          throw new QtException("Unexpected error");
                      }
                  } else {
                      arr = new ArrayRequestParam(name);
                      params->insert(name, arr);
                  }
                  arr->append(strValue);
                } else if (key.endsWith(QChar(']'))) {
                  name = key.left(key.indexOf('['));
                  if (params->contains(name)) {
                      currentArray = dynamic_cast<StringKeyArrayParam*>(params->value(name));
                      if (currentArray == NULL) {
                          throw new QtException("Unexpected error");
                      }
                  } else {
                      currentArray = new StringKeyArrayParam(name);
                      params->insert(name, currentArray);
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
                                  if (currentArray == NULL) {
                                      throw new QtException("Unexpected error");
                                  }
                              } else {
                                  StringKeyArrayParam*dimension=new StringKeyArrayParam(name);
                                  currentArray->insert(key.mid(arrayStart,arrayEnd-arrayStart),dimension);
                                  currentArray = dimension;
                              }

                           } else {
                               currentArray->insert(key.mid(arrayStart,arrayEnd-arrayStart),new ArrayValue(strValue));
                               currentArray = NULL;
                           }
                       }
                  }
                } else {
                  params->insert(key, new RequestParam<QString>(key, strValue));
                }


            }

        }
    }
}

void RequestData::parseGetParams()
{
    if (getParams == NULL) {
         getParams = new QMap<QString,AbstractRequestParam*>();
    } else {
        getParams->clear();
    }
    QString requestString = ServerData::getRequestUrl().query();
    parseParams(requestString,getParams);


}

void RequestData::parsePostParams(const FCGX_Request & request)
{
    if (QString(FCGX_GetParam("REQUEST_METHOD", request.envp))==QString("POST")) {
        if (postParams == NULL) {
             postParams = new QMap<QString,AbstractRequestParam*>();
        } else {
            postParams->clear();
        }
        QString contentLengthStr(FCGX_GetParam("CONTENT_LENGTH", request.envp));
        qDebug()<<"Content-Length:"<<contentLengthStr;
        bool ok;
        int64_t contentLength = contentLengthStr.toULongLong(&ok);
        if (!ok) {
            throw new QtException("Invalid content length");
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
    /*if ( line != NULL ) {

    }*/
}

void RequestData::parseCookies(const FCGX_Request & request)
{
    RequestData::cookies = new QMap<QString,QString>();
QStringList cookieStrLst = QString(FCGX_GetParam("HTTP_COOKIE", request.envp)).split(QChar(';'));
foreach (QString s, cookieStrLst) {
    QStringList parts = s.split(QChar('='));
    if (parts.length()==2) {
        RequestData::cookies->insert(parts.at(0).trimmed(),parts.at(1).trimmed());
    } else {
        throw new QtException("invalid cookie");
    }
}
}
QString RequestData::getString(const QString & name)
{
    if (getParams->contains(name)) {
        RequestParam<QString> * p = dynamic_cast< RequestParam<QString>* >(getParams->value(name));
        if (p == NULL) {
            throw new QtException("Parameter is not a simple value");
        }
        return p->getValue();
    } else {
        throw new QtException("Parameter does not exist");
    }
}

QString RequestData::postString(const QString &name)
{
    if (postParams->contains(name)) {
        RequestParam<QString> * p = dynamic_cast< RequestParam<QString>* >(postParams->value(name));
        if (p == NULL) {
            throw new QtException("Parameter is not a simple value");
        }
        return p->getValue();
    } else {
        throw new QtException("Parameter does not exist");
    }
}

int RequestData::getInt(const QString & name)
{
    QString value(getString(name));
    bool ok = false;
    int i = value.toInt(&ok);
    if (!ok) throw new QtException("Parameter is not a number");
    return i;
}

ArrayRequestParam *RequestData::getArray(const QString &name)
{
    if (getParams->contains(name)) {
        ArrayRequestParam * p = dynamic_cast< ArrayRequestParam* >(getParams->value(name));
        if (p == NULL) {
            throw new QtException("Parameter is not an array");
        }
        return p;
    } else {
        throw new QtException("Parameter does not exist");
    }
}

bool RequestData::isGetParamSet(const QString &name)
{
    return getParams != NULL && getParams->contains(name);
}

bool RequestData::isPostParamSet(const QString &name)
{
    return postParams != NULL && postParams->contains(name);
}

QString RequestData::cookieString(const QString &name)
{
    if(cookies->contains(name)) {
        return cookies->value(name);
    }
    throw new QtException("Cookie is not set");
}

QStringList RequestData::cookieAsArray(const QString &name)
{
    return cookieString(name).split("|");
}

bool RequestData::isCookieSet(const QString &name)
{
    return cookies->contains(name);
}
QMap<QString, AbstractRequestParam*>* RequestData::getParams = NULL;
QMap<QString, AbstractRequestParam*>* RequestData::postParams = NULL;
QMap<QString, QString>* RequestData::cookies = NULL;
