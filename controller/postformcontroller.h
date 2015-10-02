#ifndef POSTFORMCONTROLLER_H
#define POSTFORMCONTROLLER_H

#include "abstractpagecontroller.h"
#include "form/formpost.h"

class PostFormController : public AbstractPageController, public FormPost
{
protected:
    virtual unique_ptr<MvcMessage> run()=0;
    virtual unique_ptr<MvcMessage> runSubmitted()=0;
public:
    PostFormController(const QString&submitFieldName=QString("submit"));
    virtual ~PostFormController();
    virtual void runController();
};

#endif // POSTFORMCONTROLLER_H
