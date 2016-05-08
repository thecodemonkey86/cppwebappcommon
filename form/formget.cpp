#include "formget.h"
#include <QDate>
#include "exception/qtexception.h"

FormGet::FormGet(const QString&submitFieldName) : Form(submitFieldName)
{
    request = nullptr;
}


QString FormGet::stringValue(const QString &name)
{
    return request->getString(name);
}


int FormGet::intValue(const QString &name)
{
    return request->getInt(name);
}

double FormGet::doubleValue(const QString &name)
{
    return request->getDouble(name);
}

QDate FormGet::dateValue(const QString &name)
{
    if (name.count(QChar('-')) == 2) {
        return QDate::fromString(request->getString(name),QString("yyyy-MM-dd"));
    } else if (name.count(QChar('.')) == 2) {
        return QDate::fromString(request->getString(name),QString("dd.MM.yyyy"));
    } else {
        throw QtException("Invalid date format");
    }
}

bool FormGet::isSubmitted()
{
    return request->isPostParamSet(submitFieldName) && !request->getString(submitFieldName).isEmpty();
}

FormGet::~FormGet()
{

}

