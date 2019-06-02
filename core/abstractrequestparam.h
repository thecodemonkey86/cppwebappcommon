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
    virtual const QString &  toString() const=0 ;
};

#endif // ABSTRACTREQUESTPARAM_H
