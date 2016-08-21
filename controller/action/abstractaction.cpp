#include "abstractaction.h"


MultiActionController *AbstractAction::getParent() const
{
    return parent;
}

AbstractAction * AbstractAction::setParent(MultiActionController *value)
{
    AbstractAction::parent = value;
    return this;
}

AbstractAction *AbstractAction::setServerData(ServerData *value)
{
    this->serverData = value;
    return this;
}

AbstractAction *AbstractAction::setRequestData(RequestData *value)
{
    this->requestData = value;
    return this;
}

AbstractAction *AbstractAction::setSessionData(SessionData *value)
{
    this->sessionData = value;
    return this;
}



QUrl AbstractAction::getUrl()
{
    return QUrl::fromPercentEncoding((QString("/?controller=")+parent->getName()+QString("&action=")+getName()).toUtf8());
}


AbstractAction::AbstractAction()
{

}

AbstractAction::~AbstractAction()
{

}

