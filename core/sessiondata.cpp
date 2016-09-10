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

void SessionData::setSessId(const QString &value)
{
    sessId = value;
}



SessionData::SessionData(RequestData * requestData, ServerData * serverData)
{
    this->sessId = requestData->isCookieSet(SessionData::getSessionCookieName())
    ? requestData->cookieString(SessionData::getSessionCookieName())
    : Util::randString(64);
    this->sessionFileName = QDir(QDir::tempPath()).absoluteFilePath( QString("sess_%1_%2.json").arg(
                   QString::fromUtf8(QCryptographicHash::hash(serverData->getIp().toUtf8(),QCryptographicHash::Md5).toHex()),this->sessId));
    QFile f(this->sessionFileName);
    if (f.exists()) {
        if (f.open(QIODevice::ReadOnly)) {
            auto jsonDoc=QJsonDocument::fromJson(f.readAll());
            this->data = jsonDoc.object();

            f.close();
        } else {

        }
    } else {
        this->data.insert("sessionid",sessId);

    }
}

SessionData::~SessionData()
{

}

void SessionData::saveSession()
{
    QFile f(this->sessionFileName);
    if (f.open(QIODevice::WriteOnly)) {

        QJsonDocument doc;
        doc.setObject(this->data);
        f.write(doc.toJson());
        f.close();
    }
    HttpHeader::setCookie(this->sessCookieName, this->sessId);
}

const char * SessionData::sessCookieName="PHPSESSID";



