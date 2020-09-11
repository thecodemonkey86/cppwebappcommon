#include "serverdata.h"
#include <QDebug>

ServerData::~ServerData()
{

}

ServerData::ServerData(const FCGX_Request &request)
{
    QString https(FCGX_GetParam("HTTPS", request.envp));
    //qDebug()<<QStringLiteral("%1://%2%3").arg(https.isEmpty()?"http":"https", QString(FCGX_GetParam("HTTP_HOST", request.envp)),  QString(FCGX_GetParam("REQUEST_URI", request.envp)).replace(QChar('+'),QLatin1String("%20")));
    requestUrl = QUrl::fromUserInput(QStringLiteral("%1://%2%3").arg(https.isEmpty()?"http":"https", QString(FCGX_GetParam("HTTP_HOST", request.envp)),  QString(FCGX_GetParam("REQUEST_URI", request.envp)).replace(QChar('+'),QLatin1String("%20"))).toUtf8());
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


