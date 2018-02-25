#include "multiactioncontroller.h"
#include "core/requestdata.h"
#include "exception/qtexception.h"

MultiActionController::MultiActionController()
{

}

unique_ptr<MvcMessage> MultiActionController::run()
{
    if (actions.contains(requestData->getString(QString("action")))) {
       return actions.value(requestData->getString(QString("action")))->run();
    } else {
        throw QtException("No such action");
    }

}

void MultiActionController::addAction(shared_ptr<AbstractAction> action)
{
    action->setParent(this);
    actions.insert(action->getName(), action);
}

AbstractPageController *MultiActionController::setServerData(ServerData *value)
{
    AbstractPageController::setServerData(value);
    for (const  shared_ptr<AbstractAction> &a: actions.values()) {
        a->setServerData(value);
    }
    return this;
}

AbstractPageController *MultiActionController::setRequestData(RequestData *value)
{
    AbstractPageController::setRequestData(value);
    for (const  shared_ptr<AbstractAction> &a: actions.values()) {
        a->setRequestData(value);
    }
    return this;
}

AbstractPageController *MultiActionController::setSessionData(SessionData *value)
{
    AbstractPageController::setSessionData(value);
    for (const  shared_ptr<AbstractAction> &a : actions.values()) {
        a->setSessionData(value);
    }
    return this;
}

