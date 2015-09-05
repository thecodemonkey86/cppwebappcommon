#include "postformcontroller.h"
#include "view/formview.h"



PostFormController::PostFormController(const QString&submitFieldName)
{
    this->submitFieldName = submitFieldName;
}

PostFormController::~PostFormController()
{

}

void PostFormController::runController()
{
    bool submitted = isSubmitted();
    if (submitted) {
        view->update(runSubmitted());
    } else {
        view->update(run());
    }
}

