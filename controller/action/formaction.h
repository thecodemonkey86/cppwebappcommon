#ifndef FORMACTION_H
#define FORMACTION_H

#include "controller/action/action.h"
#include "controller/form.h"

class FormAction : public Action
{
protected:
    Form* form;
    virtual MvcMessage * createMvcMsg()=0;
public:
    FormAction(Form* form);
    virtual ~FormAction();
    virtual void run();
};

#endif // FORMACTION_H
