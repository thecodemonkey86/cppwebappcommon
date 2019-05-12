#include "abstractstringkeyarrayparam.h"
#include "exception/qtexception.h"
#include "stringkeyarrayparam.h"
#include "arrayvalue.h"

using namespace QtCommon2;

AbstractStringKeyArrayParam::AbstractStringKeyArrayParam()
{

}

AbstractStringKeyArrayParam::~AbstractStringKeyArrayParam()
{

}

StringKeyArrayParam *AbstractStringKeyArrayParam::stringKeyArray(const QString &key) const
{
    auto arr = dynamic_cast<StringKeyArrayParam * >(val(key));
    if(arr == nullptr) {
        throw QtException("invalid URL parameters");
    }
    return arr;
}

QString AbstractStringKeyArrayParam::stringValue(const QString &key) const
{
    auto value = dynamic_cast<ArrayValue*>(val(key));
    if(value == nullptr) {
        throw QtException("invalid URL parameters");
    }
    return value->getValue();
}

double AbstractStringKeyArrayParam::doubleValue(const QString &key) const
{
    auto value = dynamic_cast<ArrayValue*>(val(key));
    if(value == nullptr) {
        throw QtException("invalid URL parameters");
    }
    bool ok = false;
    double d = value->getValue().toDouble(&ok);
    if(!ok) {
         throw QtException("parameter is not a double value");
    }
    return d;
}


int AbstractStringKeyArrayParam::intValue(const QString &key) const
{
    auto value = dynamic_cast<ArrayValue*>(val(key));
    if(value == nullptr) {
        throw QtException("invalid URL parameters");
    }
    bool ok = false;
    int i = value->getValue().toInt(&ok);
    if(!ok) {
         throw QtException("parameter is not an int value");
    }
    return i;
}
