#include "multiactioncontroller.h"
#include "core/requestdata.h"
#include "exception/qtexception.h"

MultiActionController::MultiActionController()
{

}

void MultiActionController::run()
{
    if (actions.contains(requestData->getString(QString("action")))) {
        actions.value(requestData->getString(QString("action")))->run();
    } else {
        throw new QtException("No such action");
    }

}

void MultiActionController::addAction(QString actionName, AbstractAction *action)
{
    actions.insert(actionName, action);
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

