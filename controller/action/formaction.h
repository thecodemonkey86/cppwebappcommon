#ifndef FORMACTION_H
#define FORMACTION_H

#include "controller/action/abstractaction.h"
#include "controller/form.h"

class FormAction : public AbstractAction
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
