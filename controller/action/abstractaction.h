#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H
class MultiActionController;
#include "controller/multiactioncontroller.h"
#include "view/abstractview.h"
#include <QUrl>
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/sessiondata.h"
#include "webappcommon_global.h"
#include "sqlcon.h"
#include <memory>
using namespace std;

class MultiActionController;

class WEBAPPCOMMONSHARED_EXPORT AbstractAction
{
protected:
    MultiActionController*parent;
    shared_ptr<AbstractView> view();
    ServerData * serverData;
     RequestData * requestData;
     SessionData * sessionData;
     HttpHeader * httpHeader;
     Sql * sql;
public:
    AbstractAction();
    virtual ~AbstractAction();
    virtual unique_ptr<MvcMessage> run()=0;
    MultiActionController *getParent() const;
    void setParent(MultiActionController *value);
    void setServerData(ServerData *value);
    void setRequestData(RequestData *value);
    void setSessionData(SessionData *value);
    void setSql(Sql *value);
    void setHttpHeader(HttpHeader *value);
};

#endif // ABSTRACTACTION_H
