#ifndef MULTIACTIONCONTROLLER_H
#define MULTIACTIONCONTROLLER_H

#include <QHash>
class AbstractAction;
#include "controller/action/abstractaction.h"
#include "webappcommon_global.h"
#include "controller/abstractpagecontroller.h"
#include <memory>

using namespace std;


class WEBAPPCOMMONSHARED_EXPORT MultiActionController : public AbstractPageController
{
protected:
    QHash<QString, shared_ptr<AbstractAction>> actions;
  virtual unique_ptr<MvcMessage> run();
public:
    MultiActionController();


    void addAction( shared_ptr<AbstractAction> action);
    virtual AbstractPageController* setServerData(ServerData *value);
    virtual AbstractPageController* setRequestData(RequestData *value);
    virtual AbstractPageController* setSessionData(SessionData *value);
};

#endif // MULTIACTIONCONTROLLER_H
