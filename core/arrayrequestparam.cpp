#include "arrayrequestparam.h"
#ifdef QT_DEBUG
#include <QDebug>
#endif
ArrayRequestParam::ArrayRequestParam(const QString &name)
    : AbstractRequestParam()
{
    this->name = name;
}

ArrayRequestParam::~ArrayRequestParam()
{
    qDebug() << "destruct "+name;
}

QString ArrayRequestParam::toString() const
{
    return name;
}
