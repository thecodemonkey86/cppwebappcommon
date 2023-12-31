#pragma once

#include "form.h"
#include <QDate>
#include "webappcommon_global.h"
#include <core/requestdata.h>
#include <core/stringkeyarrayparam.h>

class WEBAPPCOMMONSHARED_EXPORT FormPost : public Form
{
  public:
  using Form::int64Value;
  using Form::stringValue;
  using Form::intValue;
  using Form:: boolValue;
  using Form:: dateValue;
  using Form:: dateTimeValue;
  using Form:: doubleValue;


    FormPost(RequestData * request,const QString&submitFieldName=QStringLiteral("submit"));
    virtual ~FormPost() override;
    virtual const QString & stringValue(const QString&name) const override;
    virtual int intValue(const QString&name) const override;
    virtual int64_t int64Value(const QString&name) const override;
    virtual uint32_t uintValue(const QString&name) const override;
    virtual QVector<int> intArrayValue(const QString&name) const override;
    virtual QVector<int64_t> int64ArrayValue(const QString&name) const override;
    virtual QSet<int64_t> int64HashSetValue(const QString&name) const override;
    virtual double doubleValue(const QString&name) const override;
    virtual QDate dateValue(const QString&name,const QString & format="yyyy-MM-dd") const override;
    virtual QDateTime dateTimeValue(const QString&name,const QString & format="yyyy-MM-ddThh:mm") const override;
    virtual QDateTime dateTimeValue(const QString&name,Qt::DateFormat format, bool toLocalTime) const override;
    virtual bool boolValue(const QString &name) const override;
    virtual bool isSubmitted() const override;

    virtual bool isValueEmpty(const QString &name) const override;
    virtual bool isSet(const QString &name) const override;
    virtual ArrayRequestParam*  array(const QString&name) const override;
     virtual QStringList stringArrayValue(const QString &name) const override;
    inline virtual StringKeyArrayParam* stringKeyArray(const QString&name) const override
    {
        return request->postStringKeyArray(name);
    }
    inline virtual  QList<QString> arrayKeys(const QString&name) const override
    {
        return request->postStringKeyArray(name)->keys();
    }
     inline virtual  const QString & arrayStringValue(const QString&fieldName,const QString&arrayKey) const override
     {
        return request->postStringKeyArray(fieldName)->stringValue(arrayKey);
     }
     inline virtual const AbstractStringKeyArrayParam*  arrayValue(const QString&fieldName,const QString&arrayKey) const override
     {
        return request->postStringKeyArray(fieldName)->val(arrayKey);
     }
    // Form interface
public:


    inline const QString & stringValueGET(const QString &name, const QString &defaultValue) const
    {
      if(!request->isGetParamSet(name))    {
        return defaultValue;
      }
      return request->getString(name);
    }
    const QString & stringValueGET(const QString &name) const;
    int intValueGET(const QString &name, int defaultValue) const;
    int intValueGET(const QString &name) const;
    int64_t int64ValueGET(const QString &name, int64_t defaultValue) const;
    int64_t int64ValueGET(const QString &name) const;
    bool boolValueGET(const QString &name) const;
    inline bool isGetParamSet(const QString &name) const {
      return request->isGetParamSet(name);
    }

    inline QVector<int64_t> int64ArrayValueGET(const QString &name) const
    {
      if(request->isGetParamSet(name))
        return  request->getInt64Array(name);
      return QVector<int64_t>();
    }

    template<class E> E enumValueGET(const QString &name, E defaultValue)
    {
      return isGetParamSet(name) ? static_cast<E>(intValueGET(name)) : defaultValue;
    }
    template<class E> E enumValueGET(const QString &name)
    {
      return static_cast<E>(intValueGET(name)) ;
    }
};


