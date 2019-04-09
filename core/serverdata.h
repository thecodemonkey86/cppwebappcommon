#ifndef SERVERDATA_H
#define SERVERDATA_H
#include "fcgio.h"
#include <QDir>
#include <QString>
#include <QUrl>
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT ServerData
{
public:
    ServerData(const FCGX_Request & request);
    virtual ~ServerData();

    const QUrl& getRequestUrl() const;
    const QString& getIp() const;
    const QString& getDocumentRoot() const;

    QDir getServerDirectory(const QString &subdir) const;
private:

    QUrl requestUrl;
    QString ip;
    QString documentRoot;
};

#endif // SERVERDATA_H
