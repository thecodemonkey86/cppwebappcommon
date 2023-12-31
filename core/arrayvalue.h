#pragma once

#include "webappcommon_global.h"
#include "abstractstringkeyarrayparam.h"

class WEBAPPCOMMONSHARED_EXPORT ArrayValue : public AbstractStringKeyArrayParam
{
protected:
    QString value;

public:
    ArrayValue(const QString &value);
    virtual ~ArrayValue();
    virtual QString  toString() const override;
    virtual const AbstractStringKeyArrayParam* val(const QString&key) const override;
    const QString &  getValue() const;

};

