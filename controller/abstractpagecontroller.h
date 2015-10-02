#ifndef ABSTRACTPAGECONTROLLER_H
#define ABSTRACTPAGECONTROLLER_H

#include "controller/abstractcontroller.h"
#include "view/template/abstracttemplate.h"
#include "view/template/htmltemplate.h"

#include "core/serverdata.h"
#include "core/requestdata.h"
#include "model/sessiondata.h"

#include <memory>
using namespace std;

class AbstractPageController : public AbstractController
{
protected:
    ServerData * serverData;
     RequestData * requestData;
     SessionData * sessionData;
     virtual unique_ptr<MvcMessage> run()=0;
public:
    AbstractPageController();
    virtual ~AbstractPageController();
    virtual QString getName()=0;

    virtual void runController();

    virtual void registerTemplate(unique_ptr<AbstractTemplate>view);
    virtual AbstractPageController* setServerData(ServerData *value);
    virtual AbstractPageController* setRequestData(RequestData *value);
    virtual AbstractPageController* setSessionData(SessionData *value);
    SessionData *getSessionData() const;
    QUrl getUrl();
};

#endif // ABSTRACTPAGECONTROLLER_H
