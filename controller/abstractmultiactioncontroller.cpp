#include "abstractmultiactioncontroller.h"
#include "core/requestdata.h"
#include "exception/qtexception.h"

AbstractMultiActionController::AbstractMultiActionController()
{

}

void AbstractMultiActionController::run()
{
    if (actions.contains(requestData->getString(QString("action")))) {
        actions.value(requestData->getString(QString("action")))->run();
    } else {
        throw new QtException("No such action");
    }

}

void AbstractMultiActionController::addAction(QString actionName, AbstractAction *action)
{
    actions.insert(actionName, action);
}

AbstractPageController *AbstractMultiActionController::setServerData(ServerData *value)
{
    AbstractPageController::setServerData(value);
    foreach (AbstractAction*a, actions.values()) {
        a->setServerData(value);
    }
    return this;
}

AbstractPageController *AbstractMultiActionController::setRequestData(RequestData *value)
{
    AbstractPageController::setRequestData(value);
    foreach (AbstractAction*a, actions.values()) {
        a->setRequestData(value);
    }
    return this;
}

