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

const QString & Form::stringValue(const QString &name, const QString &defaultValue) const
{
    if(!isSet(name)) {
        return defaultValue;
    }
    return stringValue(name);
}

int Form::intValue(const QString &name, int defaultValue) const
{
    if(!isSet(name)) {
        return defaultValue;
    }
    return intValue(name);
}

bool Form::boolValue(const QString &name, bool defaultValue) const
{
    if(!isSet(name)) {
        return defaultValue;
    }
    return boolValue(name);
}

QDate Form::dateValue(const QString &name, const QDate &defaultValue) const
{
    if(!isSet(name)) {
        return defaultValue;
    }
    return dateValue(name);
}

QDateTime Form::dateTimeValue(const QString &name, const QDateTime &defaultValue) const
{
    if(!isSet(name)) {
        return defaultValue;
    }
    return dateTimeValue(name);
}

double Form::doubleValue(const QString &name, double defaultValue) const
{
    if(!isSet(name)) {
        return defaultValue;
    }
    return doubleValue(name);
}


bool Form::isSetAndNotEmpty(const QString &name) const
{
  return isSet(name) && !isValueEmpty(name);
}

bool Form::isNotSetOrEmpty(const QString &name) const
{
  return !isSet(name) || isValueEmpty(name);
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

