#ifndef POSTFORMACTION_H
#define POSTFORMACTION_H
#include "abstractaction.h"
#include "controller/form/formpost.h"

class PostFormAction : public AbstractAction, public FormPost
{
protected:
    virtual MvcMessage* onSubmit()=0;
    virtual MvcMessage* onNonSubmit()=0;
public:
    PostFormAction(const QString&submitFieldName=QString("submit"));
    virtual MvcMessage* run();
    virtual AbstractAction *setRequestData(RequestData *value);
};

#endif // POSTFORMACTION_H
