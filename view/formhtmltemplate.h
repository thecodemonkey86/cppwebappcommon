#ifndef FORMHTMLTEMPLATE_H
#define FORMHTMLTEMPLATE_H

#include "htmltemplate.h"

class FormHtmlTemplate : public HtmlTemplate
{
public:
    FormHtmlTemplate();
    virtual void renderSubmitted();
};

#endif // FORMHTMLTEMPLATE_H
