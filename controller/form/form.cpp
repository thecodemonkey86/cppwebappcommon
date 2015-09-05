#include "form.h"
#include "exception/qtexception.h"

Form::Form(const QString&submitFieldName)
{
    this->submitFieldName = submitFieldName;
}


void Form::setRequestData(RequestData *value)
{
    request = value;
}
Form::~Form()
{

}

//bool Form::submit()
//{
//    if (requestData == nullptr) {
//        throw new QtException(QString("Form illegal state: reqdata not set"));
//    }
//    if (isSubmitted()) {
//        onSubmit();
//        return true;
//    }
//    return false;
//}

