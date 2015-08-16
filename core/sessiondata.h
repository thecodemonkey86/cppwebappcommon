#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QByteArray>
#include "model/beans/session.h"

class SessionData
{
protected:
    static Session*session;
    SessionData();
    virtual ~SessionData();
public:
    static void init(const QString &sessid,const QString &ip);
    static void set(const  QString&name,const QByteArray&value);
};

#endif // SESSIONDATA_H
