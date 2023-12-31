#pragma once

#include <QReadWriteLock>
#include <QString>
#include "webappcommon_global.h"
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
struct FCGX_Request;
class ServerData;
class HttpHeader;

/**
 * @brief manages values stored in the session data for the defined session ID provided by the http header (class HttpHeader)
 */
class WEBAPPCOMMONSHARED_EXPORT SessionData
{
public:
  static const QString KEY_SESSION_VALID_UNTIL;
protected:
    static QReadWriteLock mutex;
   static QHash<QString,QJsonObject> sessionData;
   static QDir dir;

    QString sessionHash;
    ServerData * serverData;
    HttpHeader *httpHeader;
    static int minutesSessionValid;

    public:
    static const QString SESS_COOKIE_NAME;
protected:
    QString getSessionHash(ServerData * serverData, const QString &sessId);
  static inline QString getSessionFileName(const QString &sessionHash)
  {
    //qDebug() << "filename sessid: "+this->sessId;
    return dir.absoluteFilePath( QStringLiteral("sess_%1.json").arg(
      sessionHash));
  }
    void newSession(HttpHeader *httpHeader,ServerData * serverData);
    void clearSessionImpl();
public:
    SessionData(FCGX_Request & request, ServerData * s,HttpHeader * httpHeader);
    ~SessionData();
    void setValue(const QString&key,const QString&val);
    void setValue(const QString&key,bool val);
    void setValue(const QString&key,int val);
    void setValue(const QString&key,qint64 val);
    void setValue(const QString&key,const QList<int64_t>& val);
    void setValue(const QString&key,const QStringList& val);
    void setValue(const QString&key,const QSet<int64_t>& val);
    void setValue(const QString&key,const QJsonArray & arr);
    void setValue(const QString&key,const QJsonObject & object);
    void removeValue(const QString&key);
    QString stringValue(const QString&key) const;
    bool boolValue(const QString&key, bool defaultValue = false) const;
    int intValue(const QString&key) const;
    uint uintValue(const QString&key,uint defaultValue) const;
    qint64 int64Value(const QString &key) const;
    QJsonArray jsonArrayValue(const QString &key) const;
    QJsonObject jsonObjectValue(const QString &key) const;
    static const QString  & getSessionCookieName();
    bool hasValue(const QString&key) const;
    void clearSession();
    void renewSession();
//    void setSessId(const QString &value);

    #ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
    static void saveSessions();
    void saveSession();
    static void loadSessions(const QDir & dir);
#endif
#ifdef QT_DEBUG
    void printDebug();
#endif
    static QDir getDir();
    static int getMinutesSessionValid() ;
    static void setMinutesSessionValid(int value);
    int intValue(const QString &key, int defaultValue) const;
    QString stringValue(const QString &key, QString defaultValue) const;
    QList<int64_t> int64ArrayValue(const QString &key);
    QStringList stringArrayValue(const QString &key);
    QSet<int64_t> int64HashSetValue(const QString &key);

    static void maintenance();

    template<class T> T enumValue(const QString &key, T defaultValue) const
    {
      QReadLocker lock(&mutex);
      return sessionData[sessionHash].contains(key)? static_cast<T>(sessionData[sessionHash].value(key).toInt()) : defaultValue;
    }

    static QHash<QString, QJsonObject> getAllSessionData();
    static void setValueAll(const QString& key, const QString& val, const QString& checkForKey = QString());
    static bool endSession(const QString& key);

    template<class T>
    void invalidateMultiSession(const QString &key, T value)
    {
      QWriteLocker locker(&mutex);
      QMutableHashIterator<QString,QJsonObject> it(sessionData);

        while(it.hasNext())
        {
          QString hash=it.next().key();
          if(hash != sessionHash) {
            #ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
            QFile f(getSessionFileName(hash)) ;
            #endif
            if(SessionData::sessionData[hash].contains(key)) {
              QVariant v = SessionData::sessionData[hash].value(key);
              if(v.value<T>() == value)
              {
                it.remove();
                #ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
                if(f.exists())
                  f.remove();
                #endif
              }
            }
          }
        }
    }

    template<class T>
    bool containsMultiSession(const QString &key, const T& value)
    {
      QReadLocker locker(&mutex);
      for (auto it = sessionData.cbegin(); it != sessionData.cend(); ++it) {
        if (it.key() == sessionHash) {
          continue;
        }
        if (it->contains(key)) {
          qDebug()<<it.key();
          QVariant v = it->value(key);
          if (v.value<T>() == value) {
            return true;
          }
        }
      }
      return false;
    }

    template<typename Fn>
    void invalidateMultiSession(Fn&& predicate)
    {
      QWriteLocker locker(&mutex);
      QMutableHashIterator<QString,QJsonObject> it(sessionData);

      while(it.hasNext())
      {
        auto entry = it.next();
        if (entry.key() == sessionHash) {
          continue;
        }
        if (predicate(std::as_const(entry.value()))) {
#ifdef SAVE_SESSIONS_TO_FILESYSTEM_ENABLED
          QFile f(getSessionFileName(entry.key()));
          if (f.exists()) {
            f.remove();
          }
#endif
          it.remove();
        }
      }
    }

    template<typename Fn>
    bool containsMultiSession(Fn&& predicate)
    {
      QReadLocker locker(&mutex);
      for (auto it = sessionData.cbegin(); it != sessionData.cend(); ++it) {
        if (it.key() == sessionHash) {
          continue;
        }
        if (predicate(it.value())) {
          return true;
        }
      }
      return false;
    }
};

