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
    qDebug()<<key;
    return NULL;
}

QString ArrayValue::getValue()
{
    return value;
}

