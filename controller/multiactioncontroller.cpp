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

void MultiActionController::addAction(QString actionName, Action *action)
{
    actions.insert(actionName, action);
}

PageController *MultiActionController::setServerData(ServerData *value)
{
    PageController::setServerData(value);
    foreach (Action*a, actions.values()) {
        a->setServerData(value);
    }
    return this;
}

PageController *MultiActionController::setRequestData(RequestData *value)
{
    PageController::setRequestData(value);
    foreach (Action*a, actions.values()) {
        a->setRequestData(value);
    }
    return this;
}

