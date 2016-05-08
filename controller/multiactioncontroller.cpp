#include "multiactioncontroller.h"
#include "core/requestdata.h"
#include "exception/qtexception.h"

MultiActionController::MultiActionController()
{

}

MvcMessage& MultiActionController::run()
{
    if (actions.contains(requestData->getString(QString("action")))) {
       return  actions.value(requestData->getString(QString("action")))->run();
    } else {
        throw QtException("No such action");
    }

}

void MultiActionController::addAction( AbstractAction *action)
{
    action->setParent(this);
    actions.insert(action->getName(), action);
}

AbstractPageController *MultiActionController::setServerData(ServerData *value)
{
    AbstractPageController::setServerData(value);
    foreach (AbstractAction*a, actions.values()) {
        a->setServerData(value);
    }
    return this;
}

AbstractPageController *MultiActionController::setRequestData(RequestData *value)
{
    AbstractPageController::setRequestData(value);
    foreach (AbstractAction*a, actions.values()) {
        a->setRequestData(value);
    }
    return this;
}

AbstractPageController *MultiActionController::setSessionData(SessionData *value)
{
    AbstractPageController::setSessionData(value);
    foreach (AbstractAction*a, actions.values()) {
        a->setSessionData(value);
    }
    return this;
}

