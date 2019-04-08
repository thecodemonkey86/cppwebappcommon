#include "abstractaction.h"


MultiActionController *AbstractAction::getParent() const
{
    return parent;
}

void AbstractAction::setParent(MultiActionController *value)
{
    AbstractAction::parent = value;
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



void AbstractAction::setSql(Sql *value)
{
    sql = value;
}

void AbstractAction::setHttpHeader(HttpHeader *value)
{
    httpHeader = value;
}

AbstractAction::AbstractAction()
{
    
}

AbstractAction::~AbstractAction()
{
    
}

