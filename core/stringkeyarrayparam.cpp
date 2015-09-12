#include "stringkeyarrayparam.h"
#include "arrayvalue.h"
#include <QDebug>
#include "exception/qtexception.h"

StringKeyArrayParam::StringKeyArrayParam(const QString &name) : AbstractStringKeyArrayParam()
{
    this->name = name;
}

StringKeyArrayParam::~StringKeyArrayParam()
{

}

QString StringKeyArrayParam::toString()
{
    return name;
}

QString StringKeyArrayParam::getArrayValue(int dimensionsCount,...)
{
    va_list ap;
    va_start(ap, dimensionsCount);
    AbstractStringKeyArrayParam*arr = this;
    for(int i=0;i<dimensionsCount;i++) {
        arr = arr->val(QString(va_arg(ap, const char*)));
        if (arr == NULL) {
           throw QtException("Illegal url");
        }
    }

    va_end(ap);
    ArrayValue* v=dynamic_cast<ArrayValue*>(arr);
    if (v == NULL) {
        throw QtException("Illegal url");
    }
    return v->getValue();
}

AbstractStringKeyArrayParam *StringKeyArrayParam::val(const QString &key)
{
    return this->value(key);
}



