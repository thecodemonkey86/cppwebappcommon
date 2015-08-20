#include "multiactioncontroller.h"
#include "core/requestdata.h"
#include "exception/qtexception.h"

MultiActionController::MultiActionController()
{

}

void MultiActionController::run()
{
    if (actions.contains(RequestData::getString(QString("action")))) {
        actions.value(RequestData::getString(QString("action")))->run();
    } else {
        throw new QtException("No such action");
    }

}

void MultiActionController::addAction(QString actionName, Action *action)
{
    actions.insert(actionName, action);
}

