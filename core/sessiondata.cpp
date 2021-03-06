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
    QReadLocker lock(&mutex);
    return sessionData[sessionHash].contains(key);
}

void SessionData::clearSession()
{
    QWriteLocker locker(&mutex);
    clearSessionImpl();
}

void SessionData::renewSession()
{
    QWriteLocker locker(&mutex);
    newSession(httpHeader,serverData);
}



//void SessionData::setSessId(const QString &value)
//{
//    sessId = value;
//}



void SessionData::saveSessions() {
    QWriteLocker locker(&mutex);

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
      QWriteLocker locker(&mutex);
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
     QWriteLocker locker(&mutex);
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
    QWriteLocker lock(&mutex);
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
    QWriteLocker lock(&mutex);
    sessionData[sessionHash].insert(key, QJsonValue(val));
}
void SessionData::setValue(const QString&key, bool val)
{
    QWriteLocker lock(&mutex);
    sessionData[sessionHash].insert(key, QJsonValue(val));
}

void SessionData::setValue(const QString &key, int val)
{
    QWriteLocker lock(&mutex);
    sessionData[sessionHash].insert(key, QJsonValue(val));
}

void SessionData::setValue(const QString &key, int64_t val)
{
    QWriteLocker lock(&mutex);
    sessionData[sessionHash].insert(key, QJsonValue(val));
}

void SessionData::setValue(const QString &key, const QVector<int64_t> &val)
{
  QWriteLocker lock(&mutex);
  QJsonArray arr;
  for(auto v:val) {
    arr += QJsonValue(v);
  }
  sessionData[sessionHash].insert(key,arr);
}

void SessionData::setValue(const QString &key, const QSet<int64_t> &val)
{
  QWriteLocker lock(&mutex);
  QJsonArray arr;
  for(auto v:val) {
    arr += QJsonValue(v);
  }
  sessionData[sessionHash].insert(key,arr);
}

void SessionData::setValue(const QString &key, const QJsonArray &arr)
{
    QWriteLocker lock(&mutex);
    sessionData[sessionHash].insert(key, arr);
}

void SessionData::removeValue(const QString &key)
{
    QWriteLocker lock(&mutex);
    sessionData[sessionHash].remove(key);
}

QString SessionData::stringValue(const QString &key) const
{
    QReadLocker lock(&mutex);
    return sessionData[sessionHash].value(key).toString();
}

bool SessionData::boolValue(const QString &key,bool defaultValue) const
{
    QReadLocker lock(&mutex);
    return sessionData[sessionHash].contains(key)?  sessionData[sessionHash].value(key).toBool() : defaultValue;
}

int SessionData::intValue(const QString &key) const
{
    QReadLocker lock(&mutex);
    return sessionData[sessionHash].value(key).toInt();
}

uint SessionData::uintValue(const QString &key,uint defaultValue) const
{
    QReadLocker lock(&mutex);
    return sessionData[sessionHash].contains(key)? static_cast<uint>(sessionData[sessionHash].value(key).toInt()) : defaultValue;
}

int SessionData::intValue(const QString &key, int defaultValue) const
{
  QReadLocker lock(&mutex);
  return sessionData[sessionHash].contains(key)? sessionData[sessionHash].value(key).toInt() : defaultValue;
}


QString SessionData::stringValue(const QString &key, QString defaultValue) const
{
  QReadLocker lock(&mutex);
  return sessionData[sessionHash].contains(key)? sessionData[sessionHash].value(key).toString() : defaultValue;
}

QVector<int64_t> SessionData::int64ArrayValue(const QString &key)
{
   QReadLocker lock(&mutex);
   if(! sessionData[sessionHash].contains(key))
     return QVector<int64_t>();
   auto arr = sessionData[sessionHash].value(key).toArray();

   QVector<int64_t> result(arr.size());
   int i=0;
   for(const auto & a : arr)
   {
     result[i++] = static_cast<int64_t>(a.toDouble());
   }
   return result;
}

QSet<int64_t> SessionData::int64HashSetValue(const QString &key)
{
  QReadLocker lock(&mutex);
  if(! sessionData[sessionHash].contains(key))
    return QSet<int64_t>();
  auto arr = sessionData[sessionHash].value(key).toArray();

  QSet<int64_t> result;
  for(const auto & a : arr)
  {
    result += static_cast<int64_t>(a.toDouble());
  }
  return result;
}

int64_t SessionData::int64Value(const QString &key) const
{
    QReadLocker lock(&mutex);
    return static_cast<int64_t>(sessionData[sessionHash].value(key).toDouble());
}

QJsonArray SessionData::jsonArrayValue(const QString &key) const
{
    QReadLocker lock(&mutex);
    return sessionData[sessionHash].value(key).toArray();
}








QHash<QString,QJsonObject> SessionData::sessionData;
const QString SessionData::SESS_COOKIE_NAME=QStringLiteral("PHPSESSID");
const QString SessionData::KEY_SESSION_VALID_UNTIL=QStringLiteral("__session_valid_until__");
QReadWriteLock SessionData::mutex;
QDir SessionData::dir;
int SessionData::minutesSessionValid = 24*60;
