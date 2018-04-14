#include "form.h"
#include "exception/qtexception.h"


void Form::setSessionData(SessionData *value)
{
    sessionData = value;
}

void Form::setServerData(ServerData *value)
{
    serverData = value;
}
Form::Form(RequestData * request, const QString&submitFieldName)
{
    this->submitFieldName = submitFieldName;
    this->request = request;
}



Form::~Form()
{

}

bool Form::isSetAndNotEmpty(const QString &name)
{
    return isSet(name) && !isValueEmpty(name);
}




//bool Form::submit()
//{
//    if (requestData == nullptr) {
//        throw QtException(QStringLiteral("Form illegal state: reqdata not set"));
//    }
//    if (isSubmitted()) {
//        onSubmit();
//        return true;
//    }
//    return false;
//}

