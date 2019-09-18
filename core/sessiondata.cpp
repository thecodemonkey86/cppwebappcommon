#include "sessiondata.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include "util/string/stringutil.h"
#include "requestdata.h"
#include "serverdata.h"
#include "httpheader.h"
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QDebug>

using namespace QtCommon2;

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
  if(sessionData.contains(sessId)) {
    sessionData.remove(sessId);
  }
    QFile f(getSessionFileName());
    this->sessId = QString();
    this->data = QJsonObject();

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

QString SessionData::getSessionFileName()
{
  //qDebug() << "filename sessid: "+this->sessId;
    return tempDir.absoluteFilePath( QStringLiteral("sess_%1.json").arg(
                                                       this->sessId));
}

void SessionData::newSession(HttpHeader *httpHeader,ServerData * serverData)
{
  this->sessId =  QString::fromLatin1(QCryptographicHash::hash((serverData->getIp()+StringUtil::randString(64)).toLatin1(),QCryptographicHash::Sha512).toHex());
  //qDebug() << "new session "+sessId;
  QDateTime validUntil = QDateTime::currentDateTime().addSecs(minutesSessionValid*60);
    this->data.insert(KEY_SESSION_VALID_UNTIL, validUntil.toSecsSinceEpoch());
    httpHeader->setSessionCookie(this->sessId,validUntil);
}

SessionData::SessionData(int minutesSessionValid,  ServerData * serverData, HttpHeader *httpHeader,QDir tempDir)
{
    this->tempDir = tempDir;
    this->minutesSessionValid = minutesSessionValid;
    this->serverData = serverData;
    this->httpHeader = httpHeader;
    if(httpHeader->isSessionCookieSet()) {
        this->sessId = httpHeader->getSessionCookieValue();
        if(!sessId.isEmpty()) {

            QJsonDocument jsonDoc;
 qDebug() << "sessid:"+this->sessId;
            if(sessionData.contains(this->sessId)) {
              jsonDoc = sessionData[this->sessId];
              this->data = jsonDoc.object();
             // qDebug() << jsonDoc;
            } else {

               QFile f( getSessionFileName());
               if ( f.exists()  && f.open(QIODevice::ReadOnly)) {
                 auto jsonDoc=QJsonDocument::fromJson(f.readAll());
                 this->data = jsonDoc.object();
                 sessionData[this->sessId] = jsonDoc;
                // qDebug() <<"x:"+ jsonDoc.toJson();

                 f.close();
               }else {
                // qDebug() << f.exists();
                // qDebug() << f.errorString();
                 newSession(httpHeader,serverData);
               }
            }



            if(!this->data.contains(KEY_SESSION_VALID_UNTIL) || this->data.value(KEY_SESSION_VALID_UNTIL).toVariant().value<int64_t>() < QDateTime::currentSecsSinceEpoch()) {
                clearSession();
                newSession(httpHeader,serverData);
            }
        }else {
          newSession(httpHeader,serverData);
        }
    } else {
       newSession(httpHeader,serverData);
    }


}

SessionData::~SessionData()
{

}

void SessionData::saveSession()
{
    if(!sessId.isEmpty()) {
        QFile f(getSessionFileName());
        if (f.open(QIODevice::WriteOnly|QIODevice::Truncate)) {

            QJsonDocument doc;
            doc.setObject(this->data);
            f.write(doc.toJson());
            f.close();

            sessionData[sessId] = doc;
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

void SessionData::setValue(const QString &key, qint64 val)
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

qint64 SessionData::int64Value(const QString &key) const
{
 return static_cast<qint64>(this->data.value(key).toDouble());
}

const QString SessionData::SESS_COOKIE_NAME=QStringLiteral("PHPSESSID");
const QString SessionData::KEY_SESSION_VALID_UNTIL=QStringLiteral("__session_valid_until__");



void SessionData::debug()
{
  qDebug() << data;
}

QHash<QString,QJsonDocument> SessionData::sessionData;
