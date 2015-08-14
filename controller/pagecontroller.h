#ifndef PAGECONTROLLER_H
#define PAGECONTROLLER_H

#include "controller/abstractcontroller.h"
#include "view/abstracttemplate.h"
#include "view/htmltemplate.h"

class PageController : public AbstractController
{

public:
    PageController();
    virtual ~PageController();

    virtual void run()=0;
    virtual void registerTemplate(AbstractTemplate * view);
};

#endif // PAGECONTROLLER_H
