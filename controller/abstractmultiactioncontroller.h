#ifndef ABSTRACTMULTIACTIONCONTROLLER_H
#define ABSTRACTMULTIACTIONCONTROLLER_H

#include <QMap>
#include "controller/action/abstractaction.h"

#include "controller/abstractpagecontroller.h"

class AbstractAction;

class AbstractMultiActionController : public AbstractPageController
{
protected:
    QMap<QString, AbstractAction*> actions;

public:
    AbstractMultiActionController();
    virtual void run();
    virtual QString getName()=0;
    void addAction(QString actionName, AbstractAction*action);
    virtual AbstractPageController* setServerData(ServerData *value);
    virtual AbstractPageController* setRequestData(RequestData *value);
};

#endif // ABSTRACTMULTIACTIONCONTROLLER_H
