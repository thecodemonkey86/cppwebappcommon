#ifndef POSTFORMACTION_H
#define POSTFORMACTION_H
#include "abstractaction.h"
#include "controller/form/formpost.h"

class PostFormAction : public AbstractAction, public FormPost
{
protected:
    virtual unique_ptr<MvcMessage> onSubmit()=0;
    virtual unique_ptr<MvcMessage> onNonSubmit()=0;
public:
    PostFormAction(const QString&submitFieldName=QString("submit"));
    virtual unique_ptr<MvcMessage> run();
    virtual AbstractAction *setRequestData(RequestData *value);
};

#endif // POSTFORMACTION_H
