#include "action.h"


MultiActionController *Action::getParent() const
{
    return parent;
}

Action* Action::setParent(MultiActionController *value)
{
    parent = value;
    return this;
}

Action *Action::setServerData(ServerData *value)
{
    this->serverData = value;
    return this;
}

Action *Action::setRequestData(RequestData *value)
{
    this->requestData = value;
    return this;
}



QUrl Action::getUrl()
{
    return QUrl::fromPercentEncoding((QString("/?controller=")+parent->getName()+QString("&action=")+getName()).toUtf8());
}
AbstractView *Action::view()
{
    return parent->getView();
}

Action::Action()
{

}

Action::~Action()
{

}

