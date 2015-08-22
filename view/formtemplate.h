#ifndef FORMTEMPLATE_H
#define FORMTEMPLATE_H

#include "htmltemplate.h"

class FormTemplate : public AbstractTemplate
{

public:
    FormTemplate();

    virtual void renderSubmitted()=0;
};

#endif // FORMTEMPLATE_H
