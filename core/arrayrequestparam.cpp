#include "arrayrequestparam.h"

ArrayRequestParam::ArrayRequestParam(const QString &name)
    : AbstractRequestParam(), name(name)
{
}

ArrayRequestParam::~ArrayRequestParam()
{

}

QString ArrayRequestParam::toString() const
{
    return name;
}
