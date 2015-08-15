#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
#include <QByteArray>

class SessionData
{
protected:
    static QString sessid;
    SessionData();
    virtual ~SessionData();
public:
    static void init(const QString&sessid);
    static void set(const  QString&name,const QByteArray&value);
    static bool validSession(const  QString&ip) ;
};

#endif // SESSIONDATA_H
