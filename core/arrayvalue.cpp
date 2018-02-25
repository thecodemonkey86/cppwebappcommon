#include "arrayvalue.h"
#include <QDebug>

ArrayValue::ArrayValue(const QString &value)
{
    this->value = value;
}

ArrayValue::~ArrayValue()
{

}

QString ArrayValue::toString()
{
    return value;
}

AbstractStringKeyArrayParam *ArrayValue::val(const QString&key)
{
    return nullptr;
}

QString ArrayValue::getValue()
{
    return value;
}

