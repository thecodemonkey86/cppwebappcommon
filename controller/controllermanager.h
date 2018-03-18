#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H
#include "controller_factory/controllerfactory.h"
#include "controller/abstractpagecontroller.h"
#include <QMap>
#include "util/singleton.h"
#include "view/abstractview.h"

class  ControllerManager
{



protected:

    static QMap<QString, ControllerManager*> instancesPerSession;

    Session*session;
public:
    ControllerManager* registerController(ControllerFactory*  factory);
//     ControllerManager* registerView(const QString&key,AbstractView*view);
//     AbstractView* getView(const QString&key);

    static ControllerManager*getInstance(Session* session);
     virtual ~ControllerManager();
     AbstractController* getController(const QString&name);
     AbstractPageController* getPage(const QString&name);
protected:
    ControllerManager();
    QMap< QString,ControllerFactory*> controllerFactories;
//     QMap<QString,AbstractView*> views;


};

#endif // CONTROLLERMANAGER_H
