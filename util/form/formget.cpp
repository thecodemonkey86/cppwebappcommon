#include "formget.h"
#include <QDate>
#include "exception/qtexception.h"
using namespace QtCommon2;

FormGet::FormGet(RequestData * request,const QString&submitFieldName) : Form(request,submitFieldName)
{
}


const QString & FormGet::stringValue(const QString &name) const
{
    return request->getString(name);
}


int FormGet::intValue(const QString &name) const
{
    return request->getInt(name);
}

int64_t FormGet::int64Value(const QString &name) const
{
    return request->getInt64(name);
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
    return request->isGetParamSet(submitFieldName) && !request->getString(submitFieldName).isEmpty();
}


bool FormGet::boolValue(const QString &name) const
{
    return request->getInt(name) == 1;
}


bool FormGet::isValueEmpty(const QString &name) const
{
    return request->getString(name).isEmpty();
}

bool FormGet::isSet(const QString &name) const
{
    return request->isGetParamSet(name);
}



QVector<int> FormGet::intArrayValue(const QString &name) const
{
    if(request->isGetParamSet(name))
        return  request->getIntArray(name);
    return QVector<int> ();
}

QVector<int64_t> FormGet::int64ArrayValue(const QString &name) const
{
    if(request->isGetParamSet(name))
        return  request->getInt64Array(name);
    return QVector<int64_t>();
}

QSet<int64_t> FormGet::int64HashSetValue(const QString &name) const
{
  if(request->isGetParamSet(name))
    return request->getInt64HashSet(name);
  return QSet<int64_t>();
}

ArrayRequestParam* FormGet::array(const QString &name) const
{
    return  request->getArray(name);
}


const QString & FormGet::stringValue(const QString &name, const QString &defaultValue) const
{
    return Form::stringValue(name,defaultValue);
}

int FormGet::intValue(const QString &name, int defaultValue) const
{
    return Form::intValue(name,defaultValue);
}

bool FormGet::boolValue(const QString &name, bool defaultValue) const
{
     return Form::boolValue(name,defaultValue);
}

QDate FormGet::dateValue(const QString &name, const QDate &defaultValue) const
{
    return Form::dateValue(name,defaultValue);
}

QDateTime FormGet::dateTimeValue(const QString &name, const QDateTime &defaultValue) const
{
     return Form::dateTimeValue(name,defaultValue);
}

double FormGet::doubleValue(const QString &name, double defaultValue) const
{
     return Form::doubleValue(name,defaultValue);
}



uint32_t FormGet::uintValue(const QString &name) const
{
  return request->getUInt(name);
}


QStringList FormGet::stringArrayValue(const QString &name) const
{
  return request->getStringArray(name);
}
