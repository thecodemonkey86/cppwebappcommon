#include "formaction.h"
#include "view/formview.h"

FormAction::FormAction(Form* form)
{
    this->form = form;
}

FormAction::~FormAction()
{
    delete form;
}

void FormAction::run()
{
    FormView* formView = dynamic_cast<FormView*>(view());
    bool submitted = form->submit();
    if (formView != nullptr) {
        if (submitted) {
            formView->updateSubmitted(createMvcMsg());
        } else {
            formView->update(createMvcMsg());
        }
    }

}

