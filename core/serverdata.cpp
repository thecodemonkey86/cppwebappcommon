#include "serverdata.h"


ServerData::~ServerData()
{

}

ServerData::ServerData(const FCGX_Request &request)
{
   this->requestUrl = QUrl::fromEncoded( QString(FCGX_GetParam("REQUEST_URI", request.envp)).replace(QChar('+'),QString("%20")).toUtf8(),QUrl::TolerantMode);
   this->ip = QString(FCGX_GetParam("REMOTE_ADDR", request.envp));
}
QString ServerData::getIp() const
{
    return ip;
}

QUrl ServerData::getRequestUrl() const
{
    return requestUrl;
}

void ServerData::init(const FCGX_Request &request)
{
    ServerData::instance = new ServerData(request);
}
ServerData *ServerData::getInstance()
{
    return instance;
}


ServerData * ServerData::instance = NULL;
