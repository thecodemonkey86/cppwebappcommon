#include "controllermanager.h"
#include "exception/qtexception.h"
#include "model/beans/session.h"
#include <QPair>

ControllerManager* ControllerManager::registerController(ControllerFactory * factory)
{
    this->controllerFactories.insert( factory->controllerName(), factory);
    return this;
}

ControllerManager *ControllerManager::getInstance(Session *session)
{
    if (!instancesPerSession.contains(session->getId())) {
        ControllerManager * instance = new ControllerManager();
        instancesPerSession.insert(session->getId(),instance);
        return instance;
    }
    return instancesPerSession.value(session->getId());
}

//ControllerManager *ControllerManager::registerView(const QString &key, AbstractView *view)
//{
//    this->views.insert(key,view);
//    return this;
//}

//AbstractView *ControllerManager::getView(const QString &key)
//{
//    if (this->views.contains(key)) {
//        return this->views.value(key);
//    }
//    throw new QtException(QString("No such view: ")+key);
//}


ControllerManager::ControllerManager()
{

}

ControllerManager::~ControllerManager()
{
    qDeleteAll(controllerFactories.begin(),controllerFactories.end());
}

AbstractController *ControllerManager::getController(const QString &name)
{
    if (this->controllerFactories.contains(name)) {
        return controllerFactories.value(name)->create();
    }
    throw new QtException(QString("No such controller: ")+name);
}

AbstractPageController *ControllerManager::getPage(const QString &name)
{
    if (this->controllerFactories.contains(name)) {
        AbstractPageController * p = dynamic_cast<AbstractPageController*>(controllerFactories.value(name)->create());
        if (p != NULL) {
            return p;
        }
    }
    throw new QtException(QString("No such page: ")+name);
}


QMap<QString, ControllerManager*> ControllerManager::instancesPerSession;
