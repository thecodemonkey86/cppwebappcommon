#include "multiactioncontroller.h"

MultiActionController::MultiActionController()
{

}

void MultiActionController::addAction(QString actionName, Action *action)
{
    actions.insert(actionName, action);
}

