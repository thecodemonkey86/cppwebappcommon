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
    return QUrl::fromPercentEncoding((QString("/?controller=")+parent->getName()+QString("&action=")+getName()).toUtf8());
}
Action::Action()
{

}

Action::~Action()
{

}

