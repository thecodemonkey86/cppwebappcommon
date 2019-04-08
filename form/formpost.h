#ifndef FORMPOST_H
#define FORMPOST_H
#include "form.h"
#include <QDate>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT FormPost : public Form
{
public:
    FormPost(RequestData * request,const QString&submitFieldName=QLatin1Literal("submit"));
    virtual ~FormPost();
    virtual QString stringValue(const QString&name) const;
    virtual int intValue(const QString&name) const;
    virtual QVector<int> intArrayValue(const QString&name) const;
    virtual double doubleValue(const QString&name) const;
    virtual QDate dateValue(const QString&name) const;
    virtual QDateTime dateTimeValue(const QString&name) const;
    virtual bool boolValue(const QString &name) const;
    virtual bool isSubmitted() const;

    // Form interface
public:
    virtual bool isValueEmpty(const QString &name) const;
    virtual bool isSet(const QString &name);
};


#endif // FORMPOST_H
