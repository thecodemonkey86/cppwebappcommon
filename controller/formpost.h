#ifndef FORMPOST_H
#define FORMPOST_H
#include "form.h"

class FormPost : public Form
{
protected: virtual bool isSubmitted();
public:
    FormPost(const QString&submitFieldName);
    virtual QString stringValue(const QString&name);
    virtual int intValue(const QString&name);
};

#endif // FORMPOST_H