#include "abstractpagecontroller.h"
#include "exception/qtexception.h"
#include <core/httpheader.h>
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

AbstractPageController::AbstractPageController() : view(nullptr), requestData(nullptr),serverData(nullptr),sessionData(nullptr),httpHeader(nullptr)
{
}

void AbstractPageController::registerView(std::unique_ptr<AbstractView> view)
{
    this->view = std::move(view);
}

void AbstractPageController::runController()
{
   auto viewdata = run();

   if(viewdata != nullptr) {
       this->view->setHttpHeader(httpHeader);
       if(this->view->isAutoSendHeaders()) {
         httpHeader->setContentType(this->view->getHttpContentType());
         httpHeader->finish();
       }
       try
       {
        this->view->update(std::move(viewdata));
       }
       catch(const QtCommon2::QtException & e)
       {
            qCritical().noquote() << e.getLogString();
       }
   } else{
     if(!httpHeader->getRedirectFlag())
     {
      httpHeader->setContentType(HttpHeader::CONTENT_TYPE_TEXT_PLAIN);
     }
     httpHeader->finish();
   }


}
