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


bool SessionData::hasValue(const QString &key) const
{
    QMutexLocker lock(&mutex);
    return sessionData[sessionHash].contains(key);
}

void SessionData::clearSession()
{
    QMutexLocker locker(&mutex);
    clearSessionImpl();
}

void SessionData::renewSession()
{
    QMutexLocker locker(&mutex);
    newSession(httpHeader,serverData);
}



//void SessionData::setSessId(const QString &value)
//{
//    sessId = value;
//}



void SessionData::saveSessions() {
    QMutexLocker locker(&mutex);

  auto it = SessionData::sessionData.keyValueBegin();

  while(it !=  SessionData::sessionData.keyValueEnd())
  {
      QFile f(getSessionFileName((*it).first));
      if(f.open(QIODevice::WriteOnly))
      {
          f.write(QJsonDocument((*it).second).toJson());
          // QFile destructor closes the file
      }
    ++it;
  }
}

void SessionData::saveSession()
{
      QMutexLocker locker(&mutex);
      if(!sessionHash.isEmpty()) {

        QFile f(getSessionFileName(sessionHash));
        if(f.open(QIODevice::WriteOnly))
        {
            f.write(QJsonDocument(SessionData::sessionData[sessionHash]).toJson());
            // QFile destructor closes the file
        }
      }
}

void SessionData::loadSessions(const QDir &dir)
{
     QMutexLocker locker(&mutex);
    SessionData::dir = dir;
    auto filelist = dir.entryList(QStringList() <<  QStringLiteral("sess_*.json"));
    for(const auto & file : filelist )
    {
        QFile f(dir.absoluteFilePath(file));
        if(f.open(QIODevice::ReadOnly))
        {
          QString hash = file.mid(5, file.length()-10);
          SessionData::sessionData[hash] =  QJsonDocument::fromJson(f.readAll()).object();
          if(SessionData::sessionData[hash].contains(KEY_SESSION_VALID_UNTIL)) {
               int64_t secs = SessionData::sessionData[hash].value(KEY_SESSION_VALID_UNTIL).toVariant().value<int64_t>();
              if(secs < QDateTime::currentSecsSinceEpoch())
              {
                  SessionData::sessionData.remove(hash);
                  f.remove();
              }
          } else {
              SessionData::sessionData.remove(hash);
              f.remove();
          }


        } else {
            qDebug() << f.errorString();
        }

    }
   // qDebug() << SessionData::sessionData;
}

QDir SessionData::getDir()
{
    return dir;
}

int SessionData::getMinutesSessionValid()
{
    return minutesSessionValid;
}

void SessionData::setMinutesSessionValid(int value)
{
    minutesSessionValid = value;
}

QString SessionData::getSessionHash(ServerData *serverData, const QString & sessId)
{
    return QString::fromLatin1(QCryptographicHash::hash((serverData->getIp()+sessId).toLatin1(),QCryptographicHash::Md5).toHex());
}

QString SessionData::getSessionFileName(const QString & sessionHash)
{
    //qDebug() << "filename sessid: "+this->sessId;
    return dir.absoluteFilePath( QStringLiteral("sess_%1.json").arg(
                                         sessionHash));
}

void SessionData::newSession(HttpHeader *httpHeader,ServerData * serverData)
{
    srand(QDateTime::currentMSecsSinceEpoch()%UINT32_MAX);
    QString sessId = StringUtil::randString(64);
    this->sessionHash = getSessionHash(serverData,sessId);
    QDateTime validUntil = QDateTime::currentDateTime().addSecs(minutesSessionValid*60);
    QJsonObject o;
    o.insert(KEY_SESSION_VALID_UNTIL, validUntil.toSecsSinceEpoch());
    httpHeader->setSessionCookie(sessId,serverData->getRequestUrl().host(), validUntil);
    sessionData[this->sessionHash] = o;
}

void SessionData::clearSessionImpl()
{
    QFile f(getSessionFileName(sessionHash));

    this->sessionData.remove(sessionHash);
    this->sessionHash.clear();
    if(f.exists()) {
        f.remove();
    }
    httpHeader->clearSessionCookie();
}

SessionData::SessionData(FCGX_Request & request,  ServerData * serverData, HttpHeader *httpHeader)
{
    QMutexLocker lock(&mutex);
    this->serverData = serverData;
    this->httpHeader = httpHeader;

    const char * cookieCStr = FCGX_GetParam("HTTP_COOKIE", request.envp);
    if(cookieCStr != nullptr) {
        auto cookies = QNetworkCookie::parseCookies(QByteArray(cookieCStr).replace(';','\n'));


        for(auto c : cookies) {
            if(c.name() == SessionData::getSessionCookieName().toLatin1() ) {
                QString sessId = QString::fromLatin1(c.value());

                if(!sessId.isEmpty()) {
                    this->sessionHash = getSessionHash(serverData,sessId);
                    if(sessionData.contains(sessionHash)) {


                        if(sessionData[sessionHash].contains(KEY_SESSION_VALID_UNTIL)) {
                             int64_t secs = sessionData[sessionHash].value(KEY_SESSION_VALID_UNTIL).toVariant().value<int64_t>();
                            if(secs > QDateTime::currentSecsSinceEpoch())
                            {
                                return;
                            }
                        }


                    }
                }
            }

        }
    }

    if(!this->sessionHash.isEmpty() && sessionData.contains(this->sessionHash))
    {
        clearSessionImpl();
    }

    // no requested session id or no existing session -> create new
    newSession(httpHeader,serverData);
}
SessionData::~SessionData()
{

}



void SessionData::setValue(const QString&key, const QString &val)
{
    QMutexLocker lock(&mutex);
    sessionData[sessionHash].insert(key, QJsonValue(val));
}
void SessionData::setValue(const QString&key, bool val)
{
    QMutexLocker lock(&mutex);
    sessionData[sessionHash].insert(key, QJsonValue(val));
}

void SessionData::setValue(const QString &key, int val)
{
    QMutexLocker lock(&mutex);
    sessionData[sessionHash].insert(key, QJsonValue(val));
}

void SessionData::setValue(const QString &key, qint64 val)
{
    QMutexLocker lock(&mutex);
    sessionData[sessionHash].insert(key, QJsonValue(val));
}

void SessionData::setValue(const QString &key, const QJsonArray &arr)
{
    QMutexLocker lock(&mutex);
    sessionData[sessionHash].insert(key, arr);
}

void SessionData::removeValue(const QString &key)
{
    QMutexLocker lock(&mutex);
    sessionData[sessionHash].remove(key);
}

QString SessionData::stringValue(const QString &key) const
{
    QMutexLocker lock(&mutex);
    return sessionData[sessionHash].value(key).toString();
}

bool SessionData::boolValue(const QString &key) const
{
    QMutexLocker lock(&mutex);
    return sessionData[sessionHash].value(key).toBool();
}

int SessionData::intValue(const QString &key) const
{
    QMutexLocker lock(&mutex);
    return sessionData[sessionHash].value(key).toInt();
}

int SessionData::intValue(const QString &key, int defaultValue) const
{
  QMutexLocker lock(&mutex);
  return sessionData[sessionHash].contains(key)? sessionData[sessionHash].value(key).toInt() : defaultValue;
}


QString SessionData::stringValue(const QString &key, QString defaultValue) const
{
  QMutexLocker lock(&mutex);
  return sessionData[sessionHash].contains(key)? sessionData[sessionHash].value(key).toString() : defaultValue;
}

qint64 SessionData::int64Value(const QString &key) const
{
    QMutexLocker lock(&mutex);
    return static_cast<qint64>(sessionData[sessionHash].value(key).toDouble());
}

QJsonArray SessionData::jsonArrayValue(const QString &key) const
{
    QMutexLocker lock(&mutex);
    return sessionData[sessionHash].value(key).toArray();
}








QHash<QString,QJsonObject> SessionData::sessionData;
const QString SessionData::SESS_COOKIE_NAME=QStringLiteral("PHPSESSID");
const QString SessionData::KEY_SESSION_VALID_UNTIL=QStringLiteral("__session_valid_until__");
QMutex SessionData::mutex;
QDir SessionData::dir;
int SessionData::minutesSessionValid = 24*60;
