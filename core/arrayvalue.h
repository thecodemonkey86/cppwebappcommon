#ifndef ARRAYVALUE_H
#define ARRAYVALUE_H

#include "abstractstringkeyarrayparam.h"

class ArrayValue : public AbstractStringKeyArrayParam
{
protected:
    QString value;

public:
    ArrayValue(const QString &value);
    virtual ~ArrayValue();
    virtual QString toString();
    virtual AbstractStringKeyArrayParam* val(const QString&key);
    QString getValue();

};

#endif // ARRAYVALUE_H
