#include "serverdata.h"


ServerData::~ServerData()
{

}

ServerData::ServerData()
{

}
QString ServerData::getIp()
{
    return ip;
}

QUrl ServerData::getRequestUrl()
{
    return requestUrl;
}

void ServerData::init(const FCGX_Request &request)
{
    ServerData::requestUrl = QUrl::fromEncoded( QString(FCGX_GetParam("REQUEST_URI", request.envp)).replace(QChar('+'),QString("%20")).toUtf8(),QUrl::TolerantMode);
    ServerData::ip = QString(FCGX_GetParam("REMOTE_ADDR", request.envp));
}


QUrl ServerData::requestUrl;
QString ServerData::ip;
