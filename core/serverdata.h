#ifndef SERVERDATA_H
#define SERVERDATA_H
#include "fcgio.h"
#include <QString>
#include <QUrl>

class ServerData
{
public:
    ServerData(const FCGX_Request & request);
    virtual ~ServerData();

    QUrl& getRequestUrl();
    QString getIp();

private:

    QUrl requestUrl;
    QString ip;
};

#endif // SERVERDATA_H
