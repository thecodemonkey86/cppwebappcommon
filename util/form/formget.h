#ifndef FORMGET_H
#define FORMGET_H
#include "form.h"
#include <QDate>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT FormGet : public Form
{

public:
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
    virtual const ArrayRequestParam &  array(const QString&name) const override;
     virtual QStringList stringArrayValue(const QString &name) const override;
    // Form interface
public:
    virtual const QString & stringValue(const QString &name, const QString &defaultValue) const override;
    virtual int intValue(const QString &name, int defaultValue) const override;
    virtual bool boolValue(const QString &name, bool defaultValue) const override;
    virtual QDate dateValue(const QString &name, const QDate &defaultValue) const override;
    virtual QDateTime dateTimeValue(const QString &name, const QDateTime &defaultValue) const override;
    virtual double doubleValue(const QString &name, double defaultValue) const override;
    virtual uint32_t uintValue(const QString &name) const override;


};

#endif // FORMGET_H
