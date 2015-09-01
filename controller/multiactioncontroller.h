#ifndef MULTIACTIONCONTROLLER_H
#define MULTIACTIONCONTROLLER_H

#include <QMap>
#include "controller/action/action.h"

#include "controller/abstractpagecontroller.h"

class Action;

class MultiActionController : public AbstractPageController
{
protected:
    QMap<QString, Action*> actions;

public:
    MultiActionController();
    virtual void run();
    virtual QString getName()=0;
    void addAction(QString actionName, Action*action);
    virtual AbstractPageController* setServerData(ServerData *value);
    virtual AbstractPageController* setRequestData(RequestData *value);
};

#endif // MULTIACTIONCONTROLLER_H
