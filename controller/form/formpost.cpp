#include "formpost.h"
#include <QDate>
#include "exception/qtexception.h"

FormPost::FormPost(const QString&submitFieldName) : Form(submitFieldName)
{

}


QString FormPost::stringValue(const QString &name)
{
    return request->postString(name);
}


int FormPost::intValue(const QString &name)
{
    return request->postInt(name);
}

float FormPost::doubleValue(const QString &name)
{
    return request->postDouble(name);
}

QDate FormPost::dateValue(const QString &name)
{
    if (name.count(QChar('-')) == 2) {
        return QDate::fromString(request->postString(name),QString("yyyy-MM-dd"));
    } else if (name.count(QChar('.')) == 2) {
        return QDate::fromString(request->postString(name),QString("dd.MM.yyyy"));
    } else {
        throw QtException("Invalid date format");
    }
}

bool FormPost::isSubmitted()
{
    return request->isPostParamSet(submitFieldName) && !request->postString(submitFieldName).isEmpty();
}

FormPost::~FormPost()
{

}

