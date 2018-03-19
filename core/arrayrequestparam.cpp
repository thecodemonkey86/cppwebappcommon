#include "arrayrequestparam.h"

ArrayRequestParam::ArrayRequestParam(const QString &name)
    : AbstractRequestParam()
{
    this->name = name;
}

ArrayRequestParam::~ArrayRequestParam()
{

}

QString ArrayRequestParam::toString() const
{
    return name;
}
