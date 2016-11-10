#include "sessiondata.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include "util/util.h"
#include "requestdata.h"
#include "serverdata.h"
#include "httpheader.h"
#include <QFile>
#include <QDir>

const char *SessionData::getSessionCookieName()
{
    return sessCookieName;
}

QString SessionData::getSessId() const
{
    return sessId;
}



//void SessionData::setSessId(const QString &value)
//{
//    sessId = value;
//}



QString SessionData::getSessionFileName(ServerData * serverData)
{
    return QDir(QDir::tempPath()).absoluteFilePath( QString("sess_%1_%2.json").arg(
                                                        QString::fromUtf8(QCryptographicHash::hash(serverData->getIp().toUtf8(),QCryptographicHash::Md5).toHex()),this->sessId));
}

SessionData::SessionData(RequestData * requestData, ServerData * serverData, HttpHeader *httpHeader)
{
    if(requestData->isCookieSet(SessionData::getSessionCookieName())) {
        this->sessId = requestData->cookieString(SessionData::getSessionCookieName());
        QFile f( getSessionFileName(serverData));
        if (f.exists()  && f.open(QIODevice::ReadOnly)) {
            auto jsonDoc=QJsonDocument::fromJson(f.readAll());
            this->data = jsonDoc.object();
            f.close();
        } else {
            this->sessId = Util::randString(64);
            this->data.insert("sessionid",sessId);
        }
    } else {
        this->sessId = Util::randString(64);
        this->data.insert("sessionid",sessId);
    }

    httpHeader->setCookie(this->sessCookieName, this->sessId);
    this->serverData = serverData;
}

SessionData::~SessionData()
{

}

void SessionData::saveSession()
{
    QFile f(getSessionFileName(serverData));
    if (f.open(QIODevice::WriteOnly)) {

        QJsonDocument doc;
        doc.setObject(this->data);
        f.write(doc.toJson());
        f.close();
    }

}

const char * SessionData::sessCookieName="PHPSESSID";



