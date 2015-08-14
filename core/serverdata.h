#ifndef SERVERDATA_H
#define SERVERDATA_H
#include "fcgio.h"
#include <QString>
#include <QUrl>

class ServerData
{
public:
    virtual ~ServerData();

    QUrl getRequestUrl() const;
    static void init(const FCGX_Request & request);
    static ServerData *getInstance();

private:
    static ServerData* instance;
    ServerData(const FCGX_Request & request);
    QUrl requestUrl;
};

#endif // SERVERDATA_H
