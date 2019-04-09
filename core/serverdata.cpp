#include "serverdata.h"
#include <QDebug>

ServerData::~ServerData()
{

}

ServerData::ServerData(const FCGX_Request &request)
{
    //qDebug()<<QString(FCGX_GetParam("REQUEST_URI", request.envp));
    requestUrl = QUrl::fromEncoded( QString(FCGX_GetParam("REQUEST_URI", request.envp)).replace(QChar('+'),QLatin1Literal("%20")).toUtf8(),QUrl::TolerantMode);
    ip = QString(FCGX_GetParam("REMOTE_ADDR", request.envp));
    documentRoot = QString(FCGX_GetParam("DOCUMENT_ROOT", request.envp));
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


