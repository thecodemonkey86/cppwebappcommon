#ifndef SERVERDATA_H
#define SERVERDATA_H
#include "fcgio.h"
#include <QString>
#include <QUrl>

class ServerData
{
public:
    virtual ~ServerData();

    static QUrl getRequestUrl();
    static void init(const FCGX_Request & request);
    static QString getIp();

private:
    ServerData();
    static QUrl requestUrl;
    static QString ip;
};

#endif // SERVERDATA_H
