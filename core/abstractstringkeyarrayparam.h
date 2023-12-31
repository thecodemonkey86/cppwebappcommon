#pragma once

class StringKeyArrayParam;
class QString;
#include "abstractrequestparam.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT AbstractStringKeyArrayParam : public AbstractRequestParam
{
public:
    AbstractStringKeyArrayParam();
    virtual ~AbstractStringKeyArrayParam();
    virtual const AbstractStringKeyArrayParam* val(const QString&key) const=0;
    const StringKeyArrayParam* stringKeyArray(const QString&key) const;
    const QString & stringValue(const QString&key) const;
    double doubleValue(const QString&key) const;
    int intValue(const QString&key) const;
    const QString & stringValue(int dimensionsCount, ...) const;
    const QString & stringValue(const QStringList & arrayKeys) const;
};

