#ifndef ABSTRACTSTRINGKEYARRAYPARAM_H
#define ABSTRACTSTRINGKEYARRAYPARAM_H
class StringKeyArrayParam;
#include <QString>
#include "abstractrequestparam.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT AbstractStringKeyArrayParam : public AbstractRequestParam
{
public:
    AbstractStringKeyArrayParam();
    virtual ~AbstractStringKeyArrayParam();
   virtual AbstractStringKeyArrayParam* val(const QString&key) const=0;
    StringKeyArrayParam* stringKeyArray(const QString&key) const;
    const QString & stringValue(const QString&key) const;
    double doubleValue(const QString&key) const;
    int intValue(const QString&key) const;
    const QString & stringValue(int dimensionsCount, ...) const;
    const QString & stringValue(const QStringList & arrayKeys) const;
};

#endif // ABSTRACTSTRINGKEYARRAYPARAM_H
