#ifndef MULTIACTIONCONTROLLER_H
#define MULTIACTIONCONTROLLER_H

#include <QMap>
#include "controller/action/action.h"

#include "controller/pagecontroller.h"

class Action;

class MultiActionController : public PageController
{
protected:
    QMap<QString, Action*> actions;

public:
    MultiActionController();
    virtual void run();
    virtual QString getName()=0;
    void addAction(QString actionName, Action*action);
    virtual PageController* setServerData(ServerData *value);
    virtual PageController* setRequestData(RequestData *value);
};

#endif // MULTIACTIONCONTROLLER_H
