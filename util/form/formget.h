#ifndef FORMGET_H
#define FORMGET_H
#include "form.h"
#include <QDate>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT FormGet : public Form
{
public:
  using Form::int64Value;
  using Form::stringValue;
  using Form::intValue;
     using Form:: boolValue;
     using Form:: dateValue;
     using Form:: dateTimeValue;
     using Form:: doubleValue;

    FormGet(RequestData * request,const QString&submitFieldName=QLatin1String("submit"));
    virtual ~FormGet() override = default;
    virtual const QString & stringValue(const QString&name) const override;
    virtual int intValue(const QString&name) const override;

    virtual int64_t int64Value(const QString &name) const override;
    virtual double doubleValue(const QString&name) const override;
    virtual QDate dateValue(const QString&name) const override;
    virtual QDateTime dateTimeValue(const QString&name) const override;
    virtual bool boolValue(const QString &name) const override;

    virtual bool isSubmitted() const override;

    virtual bool isValueEmpty(const QString &name) const override;
    virtual bool isSet(const QString &name)const override;

    virtual QVector<int> intArrayValue(const QString &name) const override;
    virtual QVector<int64_t> int64ArrayValue(const QString &name) const override;
     virtual QSet<int64_t> int64HashSetValue(const QString&name) const override;
    virtual ArrayRequestParam*  array(const QString&name) const override;
     virtual QStringList stringArrayValue(const QString &name) const override;
     virtual uint32_t uintValue(const QString &name) const override;

    inline virtual StringKeyArrayParam * stringKeyArray(const QString&name) const override
    {
        return request->getStringKeyArray(name);
    }
    inline virtual  QList<QString> arrayKeys(const QString&name) const override
    {
        return request->getStringKeyArray(name)->keys();
    }
     inline virtual  const QString & arrayStringValue(const QString&fieldName,const QString&arrayKey) const override
     {
        return request->getStringKeyArray(fieldName)->stringValue(arrayKey);
     }
     inline virtual AbstractStringKeyArrayParam*  arrayValue(const QString&fieldName,const QString&arrayKey) const override
     {
        return request->getStringKeyArray(fieldName)->val(arrayKey);
     }




};

#endif // FORMGET_H
