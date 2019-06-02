#include "abstractpagecontroller.h"
#include <QDebug>

RequestData *AbstractPageController::getRequestData() const
{
    return requestData;
}

void AbstractPageController::setRequestData(RequestData *value)
{
    requestData = value;
}

ServerData *AbstractPageController::getServerData() const
{
    return serverData;
}

void AbstractPageController::setServerData(ServerData *value)
{
    serverData = value;
}

SessionData *AbstractPageController::getSessionData() const
{
    return sessionData;
}

void AbstractPageController::setSessionData(SessionData *value)
{
    sessionData = value;
}

QSqlDatabase AbstractPageController::getSqlCon() const
{
    return sqlCon;
}

void AbstractPageController::setSqlCon(const QSqlDatabase &value)
{
    sqlCon = value;
}

HttpHeader *AbstractPageController::getHttpHeader() const
{
    return httpHeader;
}

void AbstractPageController::setHttpHeader(HttpHeader *value)
{
    httpHeader = value;
}

void AbstractPageController::setOutStream(FCGX_Stream *outStream)
{
    if(this->view != nullptr)
        this->view->setOutStream(outStream);
}

AbstractPageController::AbstractPageController()
{
    this->view = nullptr;
}

void AbstractPageController::registerView(unique_ptr<AbstractView> view)
{
    this->view = std::move(view);
}

void AbstractPageController::runController()
{
    if(this->view->isAutoSendHeaders()) {
         auto viewdata = run();
         httpHeader->setContentType(this->view->getHttpContentType());
         httpHeader->finish();
         if(viewdata != nullptr) {
               this->view->update(std::move(viewdata));
         }

     } else {
         auto viewdata = run();
         if(viewdata != nullptr) {
               this->view->update(std::move(viewdata));
         }
     }



}
