#ifndef ABSTRACTPAGECONTROLLER_H
#define ABSTRACTPAGECONTROLLER_H

#include "controller/abstractcontroller.h"
#include "view/template/abstracttemplate.h"
#include "view/template/htmltemplate.h"

#include "core/serverdata.h"
#include "core/requestdata.h"

class AbstractPageController : public AbstractController
{
protected:
    ServerData * serverData;
     RequestData * requestData;
public:
    AbstractPageController();
    virtual ~AbstractPageController();

    virtual void run()=0;

    virtual void registerTemplate(AbstractTemplate * view);
    virtual AbstractPageController* setServerData(ServerData *value);
    virtual AbstractPageController* setRequestData(RequestData *value);
};

#endif // ABSTRACTPAGECONTROLLER_H
