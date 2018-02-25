#include "stringkeyarrayparam.h"
#include "arrayvalue.h"
#include <QDebug>
#include "exception/qtexception.h"
using namespace QtCommon2;

StringKeyArrayParam::StringKeyArrayParam(const QString &name) : AbstractStringKeyArrayParam()
{
    this->name = name;
}

StringKeyArrayParam::~StringKeyArrayParam()
{
    qDeleteAll(QHash::begin(), QHash::end());
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
        if (arr == nullptr) {
            throw QtException(QStringLiteral("Illegal url"));
        }
    }

    va_end(ap);
    ArrayValue* v=dynamic_cast<ArrayValue*>(arr);
    if (v == nullptr) {
        throw QtException(QStringLiteral("Illegal url"));
    }
    return v->getValue();
}

QString StringKeyArrayParam::getArrayValue(const QStringList &arrayKeys)
{
    AbstractStringKeyArrayParam*arr = this;
    for(const QString & key : arrayKeys) {
        arr = arr->val(key);
    }
    ArrayValue* v=dynamic_cast<ArrayValue*>(arr);
    if (v == nullptr) {
        throw QtException(QStringLiteral("Illegal url"));
    }
    return v->getValue();
}

AbstractStringKeyArrayParam *StringKeyArrayParam::val(const QString &key)
{
    return this->value(key);
}



