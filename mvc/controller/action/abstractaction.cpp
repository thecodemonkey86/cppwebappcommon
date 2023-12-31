#include "abstractaction.h"
#include <core/httpheader.h>

void AbstractAction::runAction()
{
  if(view != nullptr)
  {
    if(this->view->isAutoSendHeaders()) {
      auto viewdata = run();
       if(viewdata != nullptr) {
          httpHeader->setContentType(this->view->getHttpContentType());
          httpHeader->finish();
          try {
            this->view->update(*viewdata);
          } catch (...) {
          }
       } else {
           if(!httpHeader->getRedirectFlag())
           {
            httpHeader->setContentType(HttpHeader::CONTENT_TYPE_TEXT_PLAIN);
           }
           httpHeader->finish();
       }
    }
    else
    {
       auto viewdata = run();
       if(viewdata != nullptr) {
          this->view->setHttpHeader(httpHeader);
           try {
            this->view->update(*viewdata);
           } catch (...) {
           }
       } else {
          if(!httpHeader->getRedirectFlag())
          {
            httpHeader->setContentType(HttpHeader::CONTENT_TYPE_TEXT_PLAIN);
          }
          httpHeader->finish();
       }
    }
  }
  else
  {
    run();
    httpHeader->finish();
  }

}

void AbstractAction::setServerData(ServerData *value)
{
    this->serverData = value;
}

void AbstractAction::setRequestData(RequestData *value)
{
    this->requestData = value;
}

void AbstractAction::setSessionData(SessionData *value)
{
    this->sessionData = value;
}


void AbstractAction::setHttpHeader(HttpHeader *value)
{
    httpHeader = value;
}

QSqlDatabase AbstractAction::getSqlCon() const
{
    return sqlCon;
}

void AbstractAction::setSqlCon(const QSqlDatabase &value)
{
    sqlCon = value;
}

void AbstractAction::setOutStream(FCGX_Stream *outStream)
{
  if(this->view != nullptr)
      this->view->setOutStream(outStream);
}


void AbstractAction::registerView(std::unique_ptr<AbstractView> view)
{
    this->view = std::move(view);
}




