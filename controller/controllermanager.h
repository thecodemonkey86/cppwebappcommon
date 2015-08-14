#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H
#include "controller_factory/controllerfactory.h"
#include "controller/pagecontroller.h"
#include <QMap>
#include "util/singleton.h"
#include "view/abstractview.h"

class  ControllerManager : public Singleton<ControllerManager>
{
    friend class Singleton<ControllerManager>;
public:
    ControllerManager* registerController(ControllerFactory * factory);
     ControllerManager* registerView(const QString&key,AbstractView*view);
     AbstractView* getView(const QString&key);
     virtual ~ControllerManager();
     AbstractController* getController(const QString&name);
     PageController* getPage(const QString&name);
protected:
    ControllerManager();
    QMap<QString,ControllerFactory*> controllerFactories;
     QMap<QString,AbstractView*> views;


};

#endif // CONTROLLERMANAGER_H
