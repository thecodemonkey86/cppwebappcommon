#ifndef ABSTRACTSTRINGKEYARRAYPARAM_H
#define ABSTRACTSTRINGKEYARRAYPARAM_H

#include <QString>
#include "abstractrequestparam.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT AbstractStringKeyArrayParam : public AbstractRequestParam
{
public:
    AbstractStringKeyArrayParam();
    virtual ~AbstractStringKeyArrayParam();
   virtual AbstractStringKeyArrayParam* val(const QString&key)=0;
};

#endif // ABSTRACTSTRINGKEYARRAYPARAM_H
