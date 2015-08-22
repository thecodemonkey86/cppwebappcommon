#ifndef FORM_H
#define FORM_H

#include <QString>
#include "core/requestdata.h"

class Form
{
protected:
    QString submitFieldName;
    virtual bool isSubmitted()=0;
public:
    Form(const QString&submitFieldName);
    virtual ~Form();
    virtual QString stringValue(const QString&name)=0;
    virtual int intValue(const QString&name)=0;
    virtual bool submit();
    virtual void onSubmit()=0;
};

#endif // FORM_H
