#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QDir>
#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>
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
 // static QHash<QString,QJsonObject> sessionData;
    QDir tempDir;
     static const QString KEY_SESSION_VALID_UNTIL;
    QJsonObject data;
    QString sessId;
    ServerData * serverData;
    HttpHeader *httpHeader;
    int minutesSessionValid;

    public:
    static const QString SESS_COOKIE_NAME;
protected:
    QString getSessionHash(ServerData * serverData);
    inline QString getSessionFileName(const QString &sessionHash);
    inline void newSession(HttpHeader *httpHeader,ServerData * serverData);
public:
    SessionData(int minutesSessionValid, const FCGX_Request &request, ServerData * s, HttpHeader * httpHeader, QDir tempDir = QDir(QDir::tempPath()));
    ~SessionData();
    void saveSession();
    void setValue(const QString&key,const QString&val);
    void setValue(const QString&key,bool val);
    void setValue(const QString&key,int val);
    void setValue(const QString&key,qint64 val);
    void setValue(const QString&key,const QJsonArray & arr);
    void removeValue(const QString&key);
    QString stringValue(const QString&key) const;
    bool boolValue(const QString&key) const;
    int intValue(const QString&key) const;
    qint64 int64Value(const QString &key) const;
    QJsonArray jsonArrayValue(const QString &key) const;
    static const QString  & getSessionCookieName();
    QString getSessId() const;
    bool hasValue(const QString&key) const;
    void clearSession();
    void renewSession();
//    void setSessId(const QString &value);
    void setTempDir(const QString &value);
    void debug();

};

#endif // SESSIONDATA_H
