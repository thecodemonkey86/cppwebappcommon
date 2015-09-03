#ifndef MULTIACTIONCONTROLLER_H
#define MULTIACTIONCONTROLLER_H

#include <QMap>
#include "controller/action/abstractaction.h"

#include "controller/abstractpagecontroller.h"

class AbstractAction;

class MultiActionController : public AbstractPageController
{
protected:
    QMap<QString, AbstractAction*> actions;

public:
    MultiActionController();
    virtual void run();
    virtual QString getName()=0;
    void addAction(QString actionName, AbstractAction*action);
    virtual AbstractPageController* setServerData(ServerData *value);
    virtual AbstractPageController* setRequestData(RequestData *value);
    virtual AbstractPageController* setSessionData(SessionData *value);
};

#endif // MULTIACTIONCONTROLLER_H
