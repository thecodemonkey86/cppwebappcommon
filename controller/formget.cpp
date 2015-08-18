#include "formget.h"

FormGet::FormGet(const QString&submitFieldName) : Form(submitFieldName)
{

}

QString FormGet::stringValue(const QString&name)
{
    return RequestData::getString(name);
}

int FormGet::intValue(const QString &name)
{
    return RequestData::getInt(name);
}

bool FormGet::isSubmitted()
{
    return RequestData::isGetParamSet(submitFieldName) && !RequestData::getString(submitFieldName).isEmpty();
}

