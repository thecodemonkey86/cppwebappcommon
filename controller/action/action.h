#ifndef ACTION_H
#define ACTION_H
#include "controller/multiactioncontroller.h"
#include "view/abstractview.h"
#include <QUrl>
#include "core/requestdata.h"
#include "core/serverdata.h"


class MultiActionController;

class Action
{
protected:
    MultiActionController*parent;
    AbstractView* view();
    ServerData * serverData;
     RequestData * requestData;
public:
    Action();
    virtual ~Action();
    virtual QString getName()=0;
    virtual void run()=0;
    MultiActionController *getParent() const;
    Action* setParent(MultiActionController *value);
    virtual Action* setServerData(ServerData *value);
    virtual Action* setRequestData(RequestData *value);
    QUrl getUrl();
};

#endif // ACTION_H
