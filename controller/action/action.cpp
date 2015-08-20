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

QUrl Action::getUrl()
{
    return QUrl::fromUserInput(QString("/?controller=")+parent->getName()+QString("&action=")+getName());
}
Action::Action()
{
    
}

