#include "formpost.h"
#include <QDate>
#include "exception/qtexception.h"
using namespace QtCommon2;

FormPost::FormPost(RequestData * request, const QString&submitFieldName) : Form(request,submitFieldName)
{
}


const QString & FormPost::stringValue(const QString &name) const
{
    return request->postString(name);
}


int FormPost::intValue(const QString &name) const
{
    return request->postInt(name);
}


int64_t FormPost::int64Value(const QString &name) const
{
     return request->postInt64(name);
}

uint32_t FormPost::uintValue(const QString &name) const
{
  return request->postUInt(name);
}

QVector<int> FormPost::intArrayValue(const QString &name) const
{
    if(request->isPostParamSet(name))
         return request->postIntArray(name);
   return QVector<int> ();
}

QVector<int64_t> FormPost::int64ArrayValue(const QString &name) const
{
    if(request->isPostParamSet(name))
        return request->postInt64Array(name);
     return QVector<int64_t> ();
}
QSet<int64_t> FormPost::int64HashSetValue(const QString &name) const
{
  if(request->isPostParamSet(name))
    return request->postInt64HashSet(name);
  return QSet<int64_t>();
}
//QJsonArray FormPost::jsonArray(const QString &name) const
//{
//  if(request->isPostParamSet(name))
//    return request->jsonArray(name);
//  return QJsonArray();
//}
double FormPost::doubleValue(const QString &name) const
{
    return request->postDouble(name);
}

QDate FormPost::dateValue(const QString &name, const QString &format) const
{
  QString d = request->postString(name);
  return QDate::fromString(d,format);
 /*   if (d.count(QChar('-')) == 2) {
        return QDate::fromString(d,QStringLiteral("yyyy-MM-dd"));
    } else if (d.count(QChar('.')) == 2) {
        return QDate::fromString(d,QStringLiteral("dd.MM.yyyy"));
    } else {
        throw QtException("Invalid date format");
    }*/
}

QDateTime FormPost::dateTimeValue(const QString &name, const QString &format) const
{
  QString d = request->postString(name);
    return QDateTime::fromString(d,format);
  /*if(!format.isNull())
  {
  } else {

    if (d.count(QChar('-')) == 2) {
        return QDateTime::fromString(d,QStringLiteral("yyyy-MM-ddThh:mm"));
    } else if (name.count(QChar('.')) == 2) {
        return QDateTime::fromString(d,QStringLiteral("dd.MM.yyyyTHH:mm:ss"));
    } else {
        throw QtException("Invalid date format");
    }
  }*/
}


bool FormPost::boolValue(const QString &name) const
{
  if(!isSet(name)) return false;
    return request->postInt(name) == 1;
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

bool FormPost::isSet(const QString &name) const
{
    return request->isPostParamSet(name);
}

ArrayRequestParam* FormPost::array(const QString &name) const
{
  return request->postArray(name);
}

QStringList FormPost::stringArrayValue(const QString &name) const
{
    if(!isSet(name))
    {
        return QStringList();
    }
    return request->postStringArray(name);
}


int FormPost::intValueGET(const QString &name, int defaultValue) const
{
  if(!request->isGetParamSet(name))    {
    return defaultValue;
  }
  return request->getInt(name);
}

int64_t FormPost::int64ValueGET(const QString &name, int64_t defaultValue) const
{
  if(!request->isGetParamSet(name))    {
    return defaultValue;
  }
  return request->getInt64(name);
}

const QString &FormPost::stringValueGET(const QString &name) const
{
  return request->getString(name);
}

int FormPost::intValueGET(const QString &name) const
{
  return request->getInt(name);
}

int64_t FormPost::int64ValueGET(const QString &name) const
{
  return request->getInt64(name);
}
