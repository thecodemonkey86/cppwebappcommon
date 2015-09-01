#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H
#include "controller/multiactioncontroller.h"
#include "view/abstractview.h"
#include <QUrl>
#include "core/requestdata.h"
#include "core/serverdata.h"

class MultiActionController;

class AbstractAction
{
protected:
    MultiActionController*parent;
    AbstractView* view();
    ServerData * serverData;
     RequestData * requestData;
public:
    AbstractAction();
    virtual ~AbstractAction();
    virtual QString getName()=0;
    virtual void run()=0;
    MultiActionController *getParent() const;
    AbstractAction* setParent(MultiActionController *value);
    virtual AbstractAction* setServerData(ServerData *value);
    virtual AbstractAction* setRequestData(RequestData *value);
    QUrl getUrl();
};

#endif // ABSTRACTACTION_H
