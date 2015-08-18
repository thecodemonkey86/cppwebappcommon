#ifndef FORMGET_H
#define FORMGET_H

#include "form.h"

class FormGet : public Form
{
protected: virtual bool isSubmitted();
public:
    FormGet(const QString&submitFieldName);
    virtual QString stringValue(const QString&name);
    virtual int intValue(const QString&name);

};

#endif // FORMGET_H
