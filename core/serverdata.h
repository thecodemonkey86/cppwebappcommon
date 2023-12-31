#pragma once

#include "webappcommon_global.h"
#include <QUrl>
#include <QDir>
struct FCGX_Request;
class WEBAPPCOMMONSHARED_EXPORT ServerData
{
public:
    ServerData(const FCGX_Request & request);
    ~ServerData();

    const QUrl& getRequestUrl() const;
    const QString& getIp() const;
    const QString& getDocumentRoot() const;

    QDir getServerDirectory(const QString &subdir) const;
private:

    QUrl requestUrl;
    QString ip;
    QString documentRoot;
};

