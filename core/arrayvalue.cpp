#include "arrayvalue.h"
#include "exception/qtexception.h"

ArrayValue::ArrayValue(const QString &value) :value(value)
{
    if(value.size()>MAX_LENGTH)
    {
        throwExceptionCriticalWithLine("request exceeds maximum size");
    }
}

ArrayValue::~ArrayValue()
{

}

QString ArrayValue::toString() const
{
    return value;
}

const AbstractStringKeyArrayParam *ArrayValue::val(const QString &key) const
{
    return nullptr;
}

const QString &  ArrayValue::getValue() const
{
    return value;
}

