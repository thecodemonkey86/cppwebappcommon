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


QSqlDatabase AbstractPageController::getSql() const
{
    return sql;
}

void AbstractPageController::setSql(const QSqlDatabase &value)
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
         view->setHttpHeader(httpHeader);
        if(view->getAutoSendHeaders()) {
            httpHeader->setContentType(view->getHttpContentType());
            httpHeader->finish();
        }

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




