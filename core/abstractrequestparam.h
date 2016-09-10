#ifndef ABSTRACTREQUESTPARAM_H
#define ABSTRACTREQUESTPARAM_H
#include "webappcommon_global.h"
#include <QString>

class WEBAPPCOMMONSHARED_EXPORT AbstractRequestParam
{
protected:

public:
    AbstractRequestParam();
    virtual ~AbstractRequestParam();
 virtual QString toString()=0;
};

#endif // ABSTRACTREQUESTPARAM_H
