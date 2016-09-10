#ifndef FORMPOST_H
#define FORMPOST_H
#include "form.h"
#include <QDate>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT FormPost : public Form
{
protected: virtual bool isSubmitted();
public:
    FormPost(const QString&submitFieldName=QString("submit"));
    virtual ~FormPost();
    virtual QString stringValue(const QString&name);
    virtual int intValue(const QString&name);
    virtual double doubleValue(const QString&name);
    virtual QDate dateValue(const QString&name);
};

#endif // FORMPOST_H
