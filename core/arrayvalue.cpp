#include "arrayvalue.h"
#include <QDebug>

ArrayValue::ArrayValue(const QString &value)
{
    this->value = value;
}

ArrayValue::~ArrayValue()
{

}

QString ArrayValue::toString() const
{
    return value;
}

AbstractStringKeyArrayParam *ArrayValue::val(const QString&key) const
{
    return nullptr;
}

QString ArrayValue::getValue() const
{
    return value;
}

