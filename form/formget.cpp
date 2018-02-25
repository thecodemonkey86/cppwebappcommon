#include "formget.h"
#include <QDate>
#include "exception/qtexception.h"
using namespace QtCommon2;

FormGet::FormGet(RequestData * request,const QString&submitFieldName) : Form(request,submitFieldName)
{
}


QString FormGet::stringValue(const QString &name) const
{
    return request->getString(name);
}


int FormGet::intValue(const QString &name) const
{
    return request->getInt(name);
}

double FormGet::doubleValue(const QString &name) const
{
    return request->getDouble(name);
}

QDate FormGet::dateValue(const QString &name) const
{
    QString d(request->getString(name));
    if (d.count(QChar('-')) == 2) {
        return QDate::fromString(d,QStringLiteral("yyyy-MM-dd"));
    } else if (d.count(QChar('.')) == 2) {
        return QDate::fromString(d,QStringLiteral("dd.MM.yyyy"));
    } else {
        throw QtException(QStringLiteral("Invalid date format"));
    }
}

QDateTime FormGet::dateTimeValue(const QString &name) const
{
    QString d(request->getString(name));
    if (d.count(QChar('-')) == 2) {
        return QDateTime::fromString(d,QStringLiteral("yyyy-MM-dd HH:mm:ss"));
    } else if (d.count(QChar('.')) == 2) {
        return QDateTime::fromString(d,QStringLiteral("dd.MM.yyyy HH:mm:ss"));
    } else {
        throw QtException(QStringLiteral("Invalid date format"));
    }
}

bool FormGet::isSubmitted() const
{
    return request->isPostParamSet(submitFieldName) && !request->getString(submitFieldName).isEmpty();
}

FormGet::~FormGet()
{

}



bool FormGet::boolValue(const QString &name) const
{
    return request->getInt(name) == 1;
}


bool FormGet::isValueEmpty(const QString &name) const
{
    return request->getString(name).isEmpty();
}

bool FormGet::isSet(const QString &name)
{
    return request->isGetParamSet(name);
}
