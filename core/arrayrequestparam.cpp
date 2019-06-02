#include "arrayrequestparam.h"

ArrayRequestParam::ArrayRequestParam(const QString &name)
    : AbstractRequestParam()
{
    this->name = name;
}

ArrayRequestParam::~ArrayRequestParam()
{

}

const QString & ArrayRequestParam::toString() const
{
    return name;
}
