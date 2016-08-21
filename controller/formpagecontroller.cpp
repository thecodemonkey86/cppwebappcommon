#include "formpagecontroller.h"

FormPageController::FormPageController(unique_ptr<Form> form)
{
    this->form = std::move(form);
}



unique_ptr<MvcMessage>FormPageController::run()
{
    if(form->isSubmitted()) {
        return onSubmitted();
    } else {
        return onNonSubmitted();
    }
}

