#include "requestparam.h"
#include "exception/qtexception.h"
#include <QUrl>
RequestParam::RequestParam(const QString &name, const QString &value) : AbstractRequestParam(),    name(name),value(value) {
    if(value.size()>MAX_LENGTH)
    {
        throwExceptionCriticalWithLine("request exceeds maximum size");
    }

}

RequestParam::RequestParam(const QString &name, uint value):  name(name),value(QString::number(value))
{

}

RequestParam::RequestParam(const QString &name, int value):  name(name),value(QString::number(value))
{
}

RequestParam::RequestParam(const QString &name, int64_t value):  name(name),value(QString::number(value))
{
}

const QString & RequestParam::getValue() const {
  return value;
}

QString RequestParam::getPercentEscapedValue() const
{
  return QString::fromUtf8(QUrl::toPercentEncoding(value));
}

QString RequestParam::toString() const{
    return name;
}

const QString &RequestParam::getName() const {
    return name;
}

void RequestParam::setName(const QString &name) {
    this->name = name;
}

