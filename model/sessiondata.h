#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QByteArray>
#include <QHash>

class Session;

class SessionData
{
protected:

//    Session*session;

    static const char * sessCookieName;

public:
    SessionData(const QString&sessionId, const QString&ipAddress);
      virtual ~SessionData();
//    void set(const  QString&name,const QByteArray&value);
//    bool existsValue(const  QString&name);
//    QString stringValue(const  QString&name);
//    Session *getSession();
//    static const char *getSessionCookieName();
};

#endif // SESSIONDATA_H
