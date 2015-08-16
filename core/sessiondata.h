#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QByteArray>
#include "model/beans/session.h"

class SessionData
{
protected:
    static Session*session;
    static const char * sessCookieName;
    SessionData();
    virtual ~SessionData();
public:
    static void init();
    static void set(const  QString&name,const QByteArray&value);
};

#endif // SESSIONDATA_H
