#include "serverdata.h"
#include "fcgiapp.h"
#include <QDebug>

ServerData::~ServerData()
{

}

ServerData::ServerData(const FCGX_Request &request)
    : requestUrl(QUrl::fromUserInput(QStringLiteral("%1://%2%3").arg(FCGX_GetParam("HTTPS", request.envp)!=nullptr&& strcmp(FCGX_GetParam("HTTPS", request.envp),"on")==0 ?QStringLiteral("https"):QStringLiteral("http"), QString(FCGX_GetParam("HTTP_HOST", request.envp)),  QString(FCGX_GetParam("REQUEST_URI", request.envp)).replace(QChar('+'),QStringLiteral("%20"))))),
      ip(FCGX_GetParam("REMOTE_ADDR", request.envp)),
      documentRoot(FCGX_GetParam("DOCUMENT_ROOT", request.envp))
{
}
const QString& ServerData::getIp() const
{
    return ip;
}

const QString& ServerData::getDocumentRoot() const
{
    return documentRoot;
}

QDir ServerData::getServerDirectory(const QString &subdir) const
{
    return QDir(documentRoot+ QDir::separator()+subdir);
}

const QUrl& ServerData::getRequestUrl() const
{
    return requestUrl;
}


