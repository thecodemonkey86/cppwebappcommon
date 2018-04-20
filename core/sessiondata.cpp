#include "sessiondata.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include "util/util.h"
#include "requestdata.h"
#include "serverdata.h"
#include "httpheader.h"
#include <QFile>
#include <QDir>
#include <QDateTime>

const QString & SessionData::getSessionCookieName()
{
    return SESS_COOKIE_NAME;
}

QString SessionData::getSessId() const
{
    return sessId;
}

bool SessionData::hasValue(const QString &key) const
{
    return this->data.contains(key);
}

void SessionData::clearSession()
{
    this->sessId = QStringLiteral("");
    this->data = QJsonObject();
    QFile f(getSessionFileName(serverData));
    if(f.exists()) {
        f.remove();
    }
    httpHeader->clearSessionCookie();
}



//void SessionData::setSessId(const QString &value)
//{
//    sessId = value;
//}



void SessionData::setTempDir(const QString &value)
{
    tempDir = QDir(value);
}

QString SessionData::getSessionFileName(ServerData * serverData)
{
    return tempDir.absoluteFilePath( QStringLiteral("sess_%1_%2.json").arg(
                                                        QString::fromUtf8(QCryptographicHash::hash(serverData->getIp().toUtf8(),QCryptographicHash::Md5).toHex()),this->sessId));
}

void SessionData::newSession(HttpHeader *httpHeader)
{
    this->sessId = Util::randString(64);
    this->data.insert(KEY_SESSION_VALID_UNTIL, QDateTime::currentDateTime().addSecs(minutesSessionValid*60).toSecsSinceEpoch());
    httpHeader->setSessionCookie(this->sessId);
}

SessionData::SessionData(int minutesSessionValid,  ServerData * serverData, HttpHeader *httpHeader,QDir tempDir)
{
    this->tempDir = tempDir;
    this->minutesSessionValid = minutesSessionValid;
    this->serverData = serverData;
    this->httpHeader = httpHeader;
    if(httpHeader->isSessionCookieSet()) {
        this->sessId = httpHeader->getSessionCookieValue();
        QFile f( getSessionFileName(serverData));
        if (f.exists()  && f.open(QIODevice::ReadOnly)) {
            auto jsonDoc=QJsonDocument::fromJson(f.readAll());
            this->data = jsonDoc.object();
            f.close();

            if(this->data.value(KEY_SESSION_VALID_UNTIL).toVariant().value<int64_t>() < QDateTime::currentSecsSinceEpoch()) {
                clearSession();
                newSession(httpHeader);
            }

        } else {
            newSession(httpHeader);
        }
    } else {
       newSession(httpHeader);
    }


}

SessionData::~SessionData()
{

}

void SessionData::saveSession()
{
    if(!sessId.isEmpty()) {
        QFile f(getSessionFileName(serverData));
        if (f.open(QIODevice::WriteOnly|QIODevice::Truncate)) {

            QJsonDocument doc;
            doc.setObject(this->data);
            f.write(doc.toJson());
            f.close();
        }
    }


}

void SessionData::setValue(const QString&key, const QString &val)
{
    this->data.insert(key, QJsonValue(val));
}
void SessionData::setValue(const QString&key, bool val)
{
    this->data.insert(key, QJsonValue(val));
}

void SessionData::removeValue(const QString &key)
{
    this->data.remove(key);
}

QString SessionData::stringValue(const QString &key) const
{
    return this->data.value(key).toString();
}

bool SessionData::boolValue(const QString &key) const
{
    return this->data.value(key).toBool();
}

int SessionData::intValue(const QString &key) const
{
 return this->data.value(key).toInt();
}

const QString SessionData::SESS_COOKIE_NAME=QStringLiteral("PHPSESSID");
const QString SessionData::KEY_SESSION_VALID_UNTIL=QStringLiteral("__session_valid_until__");


