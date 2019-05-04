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
    virtual ~MultiActionController();
    template <class T> void addAction() {
        auto action = make_shared<T>();
        action->setParent(this);
        actions.insert(T::name(), action);
    }
    template <class T> void addAction( shared_ptr<T> action) {
        action->setParent(this);
        actions.insert(T::name(), action);
    }

};

#endif // MULTIACTIONCONTROLLER_H
