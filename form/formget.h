#ifndef FORMGET_H
#define FORMGET_H
#include "form.h"
#include <QDate>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT FormGet : public Form
{

public:
    FormGet(RequestData * request,const QString&submitFieldName=QStringLiteral("submit"));
    virtual ~FormGet();
    virtual QString stringValue(const QString&name) const;
    virtual int intValue(const QString&name) const;
    virtual double doubleValue(const QString&name) const;
    virtual QDate dateValue(const QString&name) const;
    virtual QDateTime dateTimeValue(const QString&name) const;
    virtual bool boolValue(const QString &name) const;

    virtual bool isSubmitted() const;

    virtual bool isValueEmpty(const QString &name) const;
    virtual bool isSet(const QString &name);
};

#endif // FORMGET_H
