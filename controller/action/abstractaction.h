#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H
#include "controller/multiactioncontroller.h"
#include "view/abstractview.h"
#include <QUrl>
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "model/sessiondata.h"

#include <memory>
using namespace std;

class MultiActionController;

class AbstractAction
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
    virtual MvcMessage& run()=0;
    MultiActionController *getParent() const;
    AbstractAction* setParent(MultiActionController *value);
    virtual AbstractAction* setServerData(ServerData *value);
    virtual AbstractAction* setRequestData(RequestData *value);
    virtual AbstractAction* setSessionData(SessionData *value);
    QUrl getUrl();
};

#endif // ABSTRACTACTION_H
