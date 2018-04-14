#include "formpost.h"
#include <QDate>
#include "exception/qtexception.h"
using namespace QtCommon2;

FormPost::FormPost(RequestData * request, const QString&submitFieldName) : Form(request,submitFieldName)
{
}


QString FormPost::stringValue(const QString &name) const
{
    return request->postString(name);
}


int FormPost::intValue(const QString &name) const
{
    return request->postInt(name);
}

double FormPost::doubleValue(const QString &name) const
{
    return request->postDouble(name);
}

QDate FormPost::dateValue(const QString &name) const
{
    if (name.count(QChar('-')) == 2) {
        return QDate::fromString(request->postString(name),QStringLiteral("yyyy-MM-dd"));
    } else if (name.count(QChar('.')) == 2) {
        return QDate::fromString(request->postString(name),QStringLiteral("dd.MM.yyyy"));
    } else {
        throw QtException("Invalid date format");
    }
}

QDateTime FormPost::dateTimeValue(const QString &name) const
{
    if (name.count(QChar('-')) == 2) {
        return QDateTime::fromString(request->postString(name),QStringLiteral("yyyy-MM-dd HH:mm:ss"));
    } else if (name.count(QChar('.')) == 2) {
        return QDateTime::fromString(request->postString(name),QStringLiteral("dd.MM.yyyy HH:mm:ss"));
    } else {
        throw QtException("Invalid date format");
    }
}


bool FormPost::boolValue(const QString &name) const
{
    return request->getInt(name) == 1;
}

bool FormPost::isSubmitted() const
{
    return request->isPostParamSet(submitFieldName) && !request->postString(submitFieldName).isEmpty();
}

FormPost::~FormPost()
{

}



bool FormPost::isValueEmpty(const QString &name) const
{
    return request->postString(name).isEmpty();
}

bool FormPost::isSet(const QString &name)
{
    return request->isPostParamSet(name);
}
