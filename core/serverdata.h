#ifndef SERVERDATA_H
#define SERVERDATA_H
#include "fcgio.h"
#include <QString>
#include <QUrl>
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT ServerData
{
public:
    ServerData(const FCGX_Request & request);
    virtual ~ServerData();

    QUrl& getRequestUrl();
    QString& getIp();

    QString& getDocumentRoot();

private:

    QUrl requestUrl;
    QString ip;
    QString documentRoot;
};

#endif // SERVERDATA_H
