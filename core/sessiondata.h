#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include "requestdata.h"
#include "serverdata.h"
#include "httpheader.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT SessionData
{
protected:

    QJsonObject data;
    QString sessId;
    ServerData * serverData;
//    HttpHeader * httpHeader;

    public:
    static const char * sessCookieName;
protected:
    inline QString getSessionFileName(ServerData * serverData);
public:
    SessionData(RequestData * r, ServerData * s,HttpHeader * httpHeader);
      virtual ~SessionData();
    void saveSession();
    void setValue(const QString&key,const QString&val);
    QString stringValue(const QString&key);
    static const char *getSessionCookieName();
    QString getSessId() const;
//    void setSessId(const QString &value);
};

#endif // SESSIONDATA_H
