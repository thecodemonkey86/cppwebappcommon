#include "formaction.h"
#include "view/formtemplate.h"

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
    AbstractView * view= parent->getView();
    FormTemplate* tpl  = dynamic_cast< FormTemplate* >(view);
    if (form->submit()) {
        tpl->renderSubmitted();
    } else {
        tpl->render();
    }
}

