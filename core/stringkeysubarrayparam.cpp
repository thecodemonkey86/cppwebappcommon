#include "stringkeysubarrayparam.h"

StringKeySubArrayParam::StringKeySubArrayParam()
{

}

QString StringKeySubArrayParam::toString() const
{
  return join(",");
}

AbstractStringKeyArrayParam *StringKeySubArrayParam::val(const QString &key) const
{
  return nullptr;
}
