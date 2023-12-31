#include "sessiondata.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include "util/string/stringutil.h"
#include "serverdata.h"
#include "httpheader.h"
#include "fcgiapp.h"
#ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
#include <QFile>
#endif
#include <QDir>
#include <QDateTime>


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

#ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED

void SessionData::saveSessions() {
  QReadLocker locker(&mutex);

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
  QReadLocker locker(&mutex);
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


    }

  }
}

void SessionData::printDebug()
{
  qDebug()<<sessionHash;
  qDebug()<<sessionData;
}
#endif
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

QHash<QString, QJsonObject> SessionData::getAllSessionData()
{
  QReadLocker locker(&mutex);
  return sessionData;
}

void SessionData::setValueAll(const QString& key, const QString& val, const QString& checkForKey)
{
  QWriteLocker locker(&mutex);
  QMutableHashIterator<QString,QJsonObject> it(sessionData);

  while(it.hasNext())
  {
    auto entry = it.next();
    if (!checkForKey.isEmpty() && !entry.value().contains(checkForKey)) {
        continue;
    }
    entry.value().insert(key, val);
  }
}

bool SessionData::endSession(const QString &key)
{
  QWriteLocker locker(&mutex);
  return sessionData.remove(key);
}



QString SessionData::getSessionHash(ServerData *serverData, const QString & sessId)
{
  return QString::fromLatin1(QCryptographicHash::hash((serverData->getIp()+sessId).toLatin1(),QCryptographicHash::Md5).toHex());
}



void SessionData::newSession(HttpHeader *httpHeader,ServerData * serverData)
{
  QString sessId = StringUtil::randString(64);
  this->sessionHash = getSessionHash(serverData,sessId);
  QDateTime validUntil = QDateTime::currentDateTime().addSecs(minutesSessionValid*60);
  QJsonObject o;
  o.insert(KEY_SESSION_VALID_UNTIL, validUntil.toSecsSinceEpoch());
  httpHeader->setSessionCookie(sessId, serverData->getRequestUrl().host(), serverData->getRequestUrl().scheme() == "https");
  sessionData[this->sessionHash] = o;
}

void SessionData::clearSessionImpl()
{
#ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
  QFile f(getSessionFileName(sessionHash));
#endif
  this->sessionData.remove(sessionHash);
  this->sessionHash.clear();
#ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
  if(f.exists()) {
    f.remove();
  }
#endif
  httpHeader->clearSessionCookie();
}

SessionData::SessionData(FCGX_Request & request,  ServerData * serverData, HttpHeader *httpHeader):  serverData(serverData),httpHeader(httpHeader)
{
  QWriteLocker lock(&mutex);


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

void SessionData::setValue(const QString &key, const QList<int64_t> &val)
{
  QWriteLocker lock(&mutex);
  QJsonArray arr;
  for(auto v:val) {
    arr += QJsonValue(v);
  }
  sessionData[sessionHash].insert(key,arr);
}

void SessionData::setValue(const QString &key, const QStringList &val)
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

void SessionData::setValue(const QString &key, const QJsonObject &object)
{
  QWriteLocker lock(&mutex);
  sessionData[sessionHash].insert(key, object);
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

QList<int64_t> SessionData::int64ArrayValue(const QString &key)
{
  QReadLocker lock(&mutex);
  if(! sessionData[sessionHash].contains(key))
    return QList<int64_t>();
  auto arr = sessionData[sessionHash].value(key).toArray();

  QList<int64_t> result(arr.size());
  int i=0;
  for(const auto & a : arr)
  {
    result[i++] = a.toInteger();
  }
  return result;
}

QStringList SessionData::stringArrayValue(const QString &key)
{
    QReadLocker lock(&mutex);
    if(! sessionData[sessionHash].contains(key))
        return QStringList();
    auto arr = sessionData[sessionHash].value(key).toArray();

    QStringList result(arr.size());
    int i=0;
    for(const auto & a : arr)
    {
        result[i++] = a.toString();
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

void SessionData::maintenance()
{
  QWriteLocker locker(&mutex);

  auto keys = SessionData::sessionData.keys();
  for(const auto & hash : keys)
  {
#ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
    QFile f(getSessionFileName(hash)) ;
#endif
    if(SessionData::sessionData[hash].contains(KEY_SESSION_VALID_UNTIL)) {
      int64_t secs = SessionData::sessionData[hash].value(KEY_SESSION_VALID_UNTIL).toVariant().value<int64_t>();
      if(secs < QDateTime::currentSecsSinceEpoch())
      {
        sessionData.remove(hash);
#ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
        if(f.exists())
          f.remove();
#endif
      }
    } else {
      sessionData.remove(hash);
#ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
      if(f.exists())
        f.remove();
#endif
    }
  }


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

QJsonObject SessionData::jsonObjectValue(const QString &key) const
{
  QReadLocker lock(&mutex);
  return sessionData[sessionHash].value(key).toObject();
}








QHash<QString,QJsonObject> SessionData::sessionData;
const QString SessionData::SESS_COOKIE_NAME=QStringLiteral("SESSID");
const QString SessionData::KEY_SESSION_VALID_UNTIL=QStringLiteral("__session_valid_until__");
QReadWriteLock SessionData::mutex;
QDir SessionData::dir;
int SessionData::minutesSessionValid = 24*60;
