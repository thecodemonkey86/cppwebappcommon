#include "abstractpagecontroller.h"



SessionData *AbstractPageController::getSessionData() const
{
    return sessionData;
}

AbstractPageController* AbstractPageController::setSessionData(SessionData *value)
{
    sessionData = value;
    return this;
}

AbstractPageController *AbstractPageController::setHttpHeader(HttpHeader *httpHeader)
{
    this->httpHeader = httpHeader;
    return this;
}

//QUrl AbstractPageController::getUrl()
//{
//    return QUrl(QStringLiteral("/?controller=%1").arg(getName()));
//}

//QUrl AbstractPageController::getUrl(const QString &action)
//{
//    return QUrl(QStringLiteral("/?controller=%1&action=%2").arg(getName(),action));
//}

Sql *AbstractPageController::getSql() const
{
    return sql;
}

void AbstractPageController::setSql(Sql *value)
{
    sql = value;
}
AbstractPageController::AbstractPageController()
{
    
}

AbstractPageController::~AbstractPageController()
{
    
}

void AbstractPageController::runController()
{
    auto msg = run();
    httpHeader->setContentType(view->getHttpContentType());
    httpHeader->finish();
    if (!httpHeader->getRedirectFlag()) {
        if (msg != nullptr ) {
            msg->setSessionData(sessionData);
            view->update(std::move(msg));
        } else {
            view->update(nullptr);
        }
    }

}

AbstractPageController *AbstractPageController::setServerData(ServerData *value)
{
    this->serverData = value;
    return this;
}

AbstractPageController *AbstractPageController::setRequestData(RequestData *value)
{
    this->requestData = value;
    return this;
}




