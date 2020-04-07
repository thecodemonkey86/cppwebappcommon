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

QString StringKeyArrayParam::toString() const
{
    return name;
}



AbstractStringKeyArrayParam *StringKeyArrayParam::val(const QString &key) const
{
    if(!contains(key)) {
         throw QtException(QStringLiteral("no such array key: ")+key);
    }
    return this->value(key);
}



