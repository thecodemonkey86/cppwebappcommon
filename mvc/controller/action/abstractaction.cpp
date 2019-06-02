#include "abstractaction.h"


void AbstractAction::runAction()
{
    if(this->view->isAutoSendHeaders()) {
        httpHeader->setContentType(this->view->getHttpContentType());
        httpHeader->finish();
        this->view->update(run());
    } else {
        this->view->update(run());
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
    this->view->setOutStream(outStream);
}


void AbstractAction::registerView(unique_ptr<AbstractView> view)
{
    this->view = std::move(view);
}




