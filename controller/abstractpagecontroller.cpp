#include "abstractpagecontroller.h"



SessionData *AbstractPageController::getSessionData() const
{
    return sessionData;
}

void AbstractPageController::setSessionData(SessionData *value)
{
    sessionData = value;
}

void AbstractPageController::setHttpHeader(HttpHeader *httpHeader)
{
    this->httpHeader = httpHeader;
}

//QUrl AbstractPageController::getUrl()
//{
//    return QUrl(QStringLiteral("./?controller=%1").arg(getName()));
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
    if(view != nullptr) {
        httpHeader->setContentType(view->getHttpContentType());
        view->setHttpHeader(httpHeader);
        view->setHeaders();
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


}

void AbstractPageController::setServerData(ServerData *value)
{
    this->serverData = value;
}

void AbstractPageController::setRequestData(RequestData *value)
{
    this->requestData = value;
}




