#ifndef FORMGET_H
#define FORMGET_H
#include "form.h"
#include <QDate>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT FormGet : public Form
{
protected: virtual bool isSubmitted();
public:
    FormGet(const QString&submitFieldName=QString("submit"));
    virtual ~FormGet();
    virtual QString stringValue(const QString&name);
    virtual int intValue(const QString&name);
    virtual double doubleValue(const QString&name);
    virtual QDate dateValue(const QString&name);
};

#endif // FORMGET_H
