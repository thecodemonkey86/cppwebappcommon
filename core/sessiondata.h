#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QDir>
#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include "requestdata.h"
#include "serverdata.h"
#include "httpheader.h"
#include "webappcommon_global.h"

/**
 * @brief manages values stored in the session data for the defined session ID provided by the @see HttpHeader
 */
class WEBAPPCOMMONSHARED_EXPORT SessionData
{
protected:
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
    inline QString getSessionFileName(ServerData * serverData);
    inline void newSession(HttpHeader *httpHeader);
public:
    SessionData(int minutesSessionValid, ServerData * s,HttpHeader * httpHeader,QDir tempDir = QDir(QDir::tempPath()));
    ~SessionData();
    void saveSession();
    void setValue(const QString&key,const QString&val);
    void setValue(const QString&key,bool val);
    void setValue(const QString&key,int val);
    void setValue(const QString&key,qint64 val);
    void removeValue(const QString&key);
    QString stringValue(const QString&key) const;
    bool boolValue(const QString&key) const;
    int intValue(const QString&key) const;
    qint64 int64Value(const QString &key) const;
    static const QString  & getSessionCookieName();
    QString getSessId() const;
    bool hasValue(const QString&key) const;
    void clearSession();
//    void setSessId(const QString &value);
    void setTempDir(const QString &value);

};

#endif // SESSIONDATA_H
