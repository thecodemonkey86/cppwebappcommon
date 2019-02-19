#include "serverdata.h"
#include <QDebug>

ServerData::~ServerData()
{

}

ServerData::ServerData(const FCGX_Request &request)
{
    //qDebug()<<QString(FCGX_GetParam("REQUEST_URI", request.envp));
    requestUrl = QUrl::fromEncoded( QString(FCGX_GetParam("REQUEST_URI", request.envp)).replace(QChar('+'),QStringLiteral("%20")).toUtf8(),QUrl::TolerantMode);
    ip = QString(FCGX_GetParam("REMOTE_ADDR", request.envp));
    documentRoot = QString(FCGX_GetParam("DOCUMENT_ROOT", request.envp));
}
QString& ServerData::getIp()
{
    return ip;
}

QString& ServerData::getDocumentRoot()
{
    return documentRoot;
}

QUrl& ServerData::getRequestUrl()
{
    return requestUrl;
}


