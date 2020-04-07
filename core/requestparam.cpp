#include "requestparam.h"

RequestParam::RequestParam(const QString &name, const QString &value) : AbstractRequestParam() {
    this->name = name;
    this->value = value;
}

RequestParam::RequestParam(const QString &name, int value)
{
    this->name = name;
    this->value = QString::number(value);
}

RequestParam::RequestParam(const QString &name, int64_t value)
{
    this->name = name;
    this->value = QString::number(value);
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

