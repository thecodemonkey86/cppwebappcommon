#include "formget.h"

FormGet::FormGet(const QString&submitFieldName) : Form(submitFieldName)
{

}

QString FormGet::stringValue(const QString&name)
{
    return requestData->getString(name);
}

int FormGet::intValue(const QString &name)
{
    return requestData->getInt(name);
}

bool FormGet::isSubmitted()
{
    return requestData->isGetParamSet(submitFieldName) && !requestData->getString(submitFieldName).isEmpty();
}

FormGet::~FormGet()
{

}

