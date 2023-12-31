#include "form.h"
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/sessiondata.h"


void Form::setSessionData(SessionData *value)
{
    sessionData = value;
}

void Form::setServerData(ServerData *value)
{
    serverData = value;
}
QString Form::getSubmitFieldName() const
{
    return submitFieldName;
}

Form::Form(RequestData * request, const QString&submitFieldName):    submitFieldName(submitFieldName),request(request),serverData(nullptr),sessionData(nullptr)
{

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


int64_t Form::int64Value(const QString &name, int64_t defaultValue) const
{
  if(!isSet(name)) {
    return defaultValue;
  }
  return int64Value(name);
}

bool Form::boolValue(const QString &name, bool defaultValue) const
{
    if(!isSet(name)) {
        return defaultValue;
    }
    return boolValue(name);
}

QDate Form::dateValue(const QString &name, const QDate &defaultValue,const QString&format) const
{
    if(isNotSetOrEmpty(name)) {
        return defaultValue;
    }
    return dateValue(name,format);
}

QDateTime Form::dateTimeValue(const QString &name, const QDateTime &defaultValue,const QString&format) const
{
    if(isNotSetOrEmpty(name)) {
        return defaultValue;
    }
    return dateTimeValue(name,format);
}
QDateTime Form::dateTimeValue(const QString &name, const QDateTime &defaultValue, Qt::DateFormat format, bool toLocalTime) const
{
  if(isNotSetOrEmpty(name)) {
    return defaultValue;
  }
  return dateTimeValue(name,format,toLocalTime);
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


uint Form::uintValue(const QString &name, uint defaultValue) const
{
  if(!isSet(name)) {
    return defaultValue;
  }
  return uintValue(name);
}
