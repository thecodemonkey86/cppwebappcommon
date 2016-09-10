#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H
#include "controller/multiactioncontroller.h"
#include "view/abstractview.h"
#include <QUrl>
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/sessiondata.h"
#include "webappcommon_global.h"
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
public:
    AbstractAction();
    virtual ~AbstractAction();
    virtual QString getName()=0;
    virtual unique_ptr<MvcMessage> run()=0;
    MultiActionController *getParent() const;
    AbstractAction* setParent(MultiActionController *value);
    virtual AbstractAction* setServerData(ServerData *value);
    virtual AbstractAction* setRequestData(RequestData *value);
    virtual AbstractAction* setSessionData(SessionData *value);
    QUrl getUrl();
};

#endif // ABSTRACTACTION_H
