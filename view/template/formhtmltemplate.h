#ifndef FORMHTMLTEMPLATE_H
#define FORMHTMLTEMPLATE_H

#include "htmltemplate.h"
#include "view/formview.h"

class FormHtmlTemplate : public HtmlTemplate, public FormView
{
public:
    FormHtmlTemplate();
    virtual void updateSubmitted(MvcMessage*updateMsg);
    virtual void update(MvcMessage*updateMsg);
};

#endif // FORMHTMLTEMPLATE_H
