#include "form.h"


Form::Form(const QString&submitFieldName)
{
    this->submitFieldName = submitFieldName;
}

Form::~Form()
{

}

bool Form::submit()
{
    if (isSubmitted()) {
        onSubmit();
        return true;
    }
    return false;
}

