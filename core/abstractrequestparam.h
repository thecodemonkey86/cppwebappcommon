#pragma once

#include "webappcommon_global.h"
#include <QString>

class WEBAPPCOMMONSHARED_EXPORT AbstractRequestParam
{
protected:
   static const constexpr int MAX_LENGTH=1024*1024;
public:
    AbstractRequestParam();
    virtual ~AbstractRequestParam();
    virtual QString  toString() const=0 ;
};

