#ifndef PAGECONTROLLER_H
#define PAGECONTROLLER_H

#include "controller/abstractcontroller.h"
#include "view/template/abstracttemplate.h"
#include "view/template/htmltemplate.h"

#include "core/serverdata.h"
#include "core/requestdata.h"

class PageController : public AbstractController
{
protected:
    ServerData * serverData;
     RequestData * requestData;
public:
    PageController();
    virtual ~PageController();

    virtual void run()=0;

    virtual void registerTemplate(AbstractTemplate * view);
    virtual PageController* setServerData(ServerData *value);
    virtual PageController* setRequestData(RequestData *value);
};

#endif // PAGECONTROLLER_H
