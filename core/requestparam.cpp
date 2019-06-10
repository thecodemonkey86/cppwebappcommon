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

const QString & RequestParam::getValue() const {
    return value;
}

const QString &  RequestParam::toString() const{
    return name;
}

const QString &RequestParam::getName() const {
    return name;
}

void RequestParam::setName(const QString &name) {
    this->name = name;
}
