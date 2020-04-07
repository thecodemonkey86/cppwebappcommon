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
        throwExceptionWithLine("invalid URL parameters");
    }
    return arr;
}

const QString & AbstractStringKeyArrayParam::stringValue(const QString &key) const
{
    auto value = dynamic_cast<ArrayValue*>(val(key));
    if(value == nullptr) {
        throwExceptionWithLine("invalid URL parameters");
    }
    return value->getValue();
}

double AbstractStringKeyArrayParam::doubleValue(const QString &key) const
{
    auto value = dynamic_cast<ArrayValue*>(val(key));
    if(value == nullptr) {
        throwExceptionWithLine("invalid URL parameters");
    }
    bool ok = false;
    double d = value->getValue().toDouble(&ok);
    if(!ok) {
         throwExceptionWithLine("parameter is not a double value");
    }
    return d;
}


int AbstractStringKeyArrayParam::intValue(const QString &key) const
{
    auto value = dynamic_cast<ArrayValue*>(val(key));
    if(value == nullptr) {
        throwExceptionWithLine("invalid URL parameters");
    }
    bool ok = false;
    int i = value->getValue().toInt(&ok);
    if(!ok) {
         throwExceptionWithLine("parameter is not an int value");
    }
    return i;
}

const QString & AbstractStringKeyArrayParam::stringValue(int dimensionsCount,...) const
{
    va_list ap;
    va_start(ap, dimensionsCount);
    const AbstractStringKeyArrayParam*arr = this;
    for(int i=0;i<dimensionsCount;i++) {
        arr = arr->val(QString(va_arg(ap, const char*)));
        if (arr == nullptr) {
            throw QtException(QStringLiteral("Illegal url"));
        }
    }

    va_end(ap);
    const ArrayValue* v=dynamic_cast<const ArrayValue*>(arr);
    if (v == nullptr) {
        throw QtException(QStringLiteral("Illegal url"));
    }
    return v->getValue();
}

const QString & AbstractStringKeyArrayParam::stringValue(const QStringList &arrayKeys) const
{
    const AbstractStringKeyArrayParam*arr = this;
    for(const QString & key : arrayKeys) {
        arr = arr->val(key);
    }
    const ArrayValue* v=dynamic_cast<const ArrayValue*>(arr);
    if (v == nullptr) {
        throw QtException(QStringLiteral("Illegal url"));
    }
    return v->getValue();
}
