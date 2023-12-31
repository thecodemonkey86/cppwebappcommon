#ifndef MULTIACTIONCONTROLLER_H
#define MULTIACTIONCONTROLLER_H

#include <QHash>
class AbstractAction;
#include "mvc/controller/action/abstractaction.h"
#include "webappcommon_global.h"
#include "mvc/controller/abstractpagecontroller.h"
#include <memory>
#include <mvc/model/viewdata.h>


/**
 * @brief abstract base class for multi action page controllers
 */
class WEBAPPCOMMONSHARED_EXPORT MultiActionPageController : public AbstractPageController
{
protected:
    QHash<QString, std::shared_ptr<AbstractAction>> actions;
    std::shared_ptr<AbstractAction> defaultAction;
  virtual std::unique_ptr<ViewData> run() override;

public:
    virtual void runController() override;
    MultiActionPageController() = default;
    virtual ~MultiActionPageController() override = default;
    template <class A> std::shared_ptr<A> addAction(bool setDefaultAction = false) {
        auto action = std::make_shared<A>();
        actions.insert(A::name(), action);
        if(setDefaultAction)
        {
          this->defaultAction = action;
        }
        return action;
    }



    // AbstractPageController interface
public:
    virtual void setOutStream(FCGX_Stream *outStream) override;
};

#endif // MULTIACTIONCONTROLLER_H
