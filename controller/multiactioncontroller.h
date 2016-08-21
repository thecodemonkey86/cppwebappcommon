#ifndef MULTIACTIONCONTROLLER_H
#define MULTIACTIONCONTROLLER_H

#include <QHash>
#include "controller/action/abstractaction.h"

#include "controller/abstractpagecontroller.h"

class AbstractAction;

class MultiActionController : public AbstractPageController
{
protected:
    QHash<QString, AbstractAction*> actions;
  virtual unique_ptr<MvcMessage> run();
public:
    MultiActionController();


    void addAction(AbstractAction *action);
    virtual AbstractPageController* setServerData(ServerData *value);
    virtual AbstractPageController* setRequestData(RequestData *value);
    virtual AbstractPageController* setSessionData(SessionData *value);
};

#endif // MULTIACTIONCONTROLLER_H
