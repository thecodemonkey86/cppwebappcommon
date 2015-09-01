#ifndef FORMVIEW_H
#define FORMVIEW_H

#include "view/template/htmltemplate.h"

class FormView : public AbstractView
{

public:
    FormView();

    virtual void updateSubmitted(MvcMessage*updateMsg)=0;
};

#endif // FORMVIEW_H
