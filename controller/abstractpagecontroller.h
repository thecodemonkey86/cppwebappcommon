#ifndef ABSTRACTPAGECONTROLLER_H
#define ABSTRACTPAGECONTROLLER_H

#include "controller/abstractcontroller.h"
#include "view/template/htmltemplate.h"

#include "core/serverdata.h"
#include "core/requestdata.h"
#include "core/sessiondata.h"
#include "sqlcon.h"
#include <memory>
#include "webappcommon_global.h"
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT AbstractPageController : public AbstractController
{
protected:
    ServerData * serverData;
     RequestData * requestData;
     SessionData * sessionData;
     HttpHeader *  httpHeader;
     Sql * sql;
     virtual unique_ptr<MvcMessage> run()=0;
public:
    AbstractPageController();
    virtual ~AbstractPageController();
    virtual QString getName()=0;

    virtual void runController();

//    virtual void registerTemplate(unique_ptr<AbstractTemplate>view);
    virtual AbstractPageController* setServerData(ServerData *value);
    virtual AbstractPageController* setRequestData(RequestData *value);
    virtual AbstractPageController* setSessionData(SessionData *value);
     virtual AbstractPageController* setHttpHeader(HttpHeader *  httpHeader);
    SessionData *getSessionData() const;
    QUrl getUrl();
    Sql *getSql() const;
    void setSql(Sql *value);
};

#endif // ABSTRACTPAGECONTROLLER_H
