#ifndef FORMPAGECONTROLLER_H
#define FORMPAGECONTROLLER_H
#include "abstractpagecontroller.h"
#include "form/form.h"

#include <memory>
using namespace std;

class FormPageController : public AbstractPageController
{
protected:
    unique_ptr<Form> form;
public:
    FormPageController(unique_ptr<Form> form);


    // AbstractPageController interface
protected:
    virtual unique_ptr<MvcMessage>run();
     virtual unique_ptr<MvcMessage>onSubmitted()=0;
    virtual unique_ptr<MvcMessage>onNonSubmitted()=0;

};

#endif // FORMPAGECONTROLLER_H
