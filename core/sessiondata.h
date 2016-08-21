#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include "requestdata.h"
#include "serverdata.h"

class SessionData
{
protected:

    QJsonObject data;
    QString sessionFileName;
    QString sessId;
    public:
    static const char * sessCookieName;

public:
    SessionData(RequestData * r, ServerData * s);
      virtual ~SessionData();
    void saveSession();
    static const char *getSessionCookieName();
    QString getSessId() const;
    void setSessId(const QString &value);
};

#endif // SESSIONDATA_H
