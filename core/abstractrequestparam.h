#ifndef ABSTRACTREQUESTPARAM_H
#define ABSTRACTREQUESTPARAM_H

#include <QString>

class AbstractRequestParam
{
protected:

public:
    AbstractRequestParam();
    virtual ~AbstractRequestParam();
 virtual QString toString()=0;
};

#endif // ABSTRACTREQUESTPARAM_H
