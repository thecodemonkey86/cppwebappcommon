#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QDir>
#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>
#include <QReadWriteLock>
#include "requestdata.h"
#include "serverdata.h"
#include "httpheader.h"
#include "webappcommon_global.h"

/**
 * @brief manages values stored in the session data for the defined session ID provided by the http header (class HttpHeader)
 */
class WEBAPPCOMMONSHARED_EXPORT SessionData
{
protected:
    static QReadWriteLock mutex;
   static QHash<QString,QJsonObject> sessionData;
   static QDir dir;
     static const QString KEY_SESSION_VALID_UNTIL;
    QString sessionHash;
    ServerData * serverData;
    HttpHeader *httpHeader;
    static int minutesSessionValid;

    public:
    static const QString SESS_COOKIE_NAME;
protected:
    QString getSessionHash(ServerData * serverData, const QString &sessId);
    static inline QString getSessionFileName(const QString &sessionHash);
    inline void newSession(HttpHeader *httpHeader,ServerData * serverData);
    inline void clearSessionImpl();
public:
    SessionData(FCGX_Request & request, ServerData * s,HttpHeader * httpHeader);
    ~SessionData();
    void setValue(const QString&key,const QString&val);
    void setValue(const QString&key,bool val);
    void setValue(const QString&key,int val);
    void setValue(const QString&key,qint64 val);
    void setValue(const QString&key,const QVector<int64_t>& val);
    void setValue(const QString&key,const QSet<int64_t>& val);
    void setValue(const QString&key,const QJsonArray & arr);
    void removeValue(const QString&key);
    QString stringValue(const QString&key) const;
    bool boolValue(const QString&key, bool defaultValue = false) const;
    int intValue(const QString&key) const;
    uint uintValue(const QString&key,uint defaultValue) const;
    qint64 int64Value(const QString &key) const;
    QJsonArray jsonArrayValue(const QString &key) const;
    static const QString  & getSessionCookieName();
    bool hasValue(const QString&key) const;
    void clearSession();
    void renewSession();
//    void setSessId(const QString &value);

    static void saveSessions();
    void saveSession();
    static void loadSessions(const QDir & dir);
    static QDir getDir();
    static int getMinutesSessionValid() ;
    static void setMinutesSessionValid(int value);
    int intValue(const QString &key, int defaultValue) const;
    QString stringValue(const QString &key, QString defaultValue) const;
    QVector<int64_t> int64ArrayValue(const QString &key);
    QSet<int64_t> int64HashSetValue(const QString &key);

    template<class T> T enumValue(const QString &key, T defaultValue) const
    {
      QReadLocker lock(&mutex);
      return sessionData[sessionHash].contains(key)? static_cast<T>(sessionData[sessionHash].value(key).toInt()) : defaultValue;
    }

};

#endif // SESSIONDATA_H
