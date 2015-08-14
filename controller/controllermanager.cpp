#include "controllermanager.h"
#include "exception/qtexception.h"

ControllerManager* ControllerManager::registerController(ControllerFactory * factory)
{
    this->controllerFactories.insert(factory->controllerName(), factory);
    return this;
}

ControllerManager *ControllerManager::registerView(const QString &key, AbstractView *view)
{
    this->views.insert(key,view);
    return this;
}

AbstractView *ControllerManager::getView(const QString &key)
{
    if (this->views.contains(key)) {
        return this->views.value(key);
    }
    throw new QtException(QString("No such view: ")+key);
}


ControllerManager::ControllerManager()
{

}

ControllerManager::~ControllerManager()
{

}

AbstractController *ControllerManager::getController(const QString &name)
{
    if (this->controllerFactories.contains(name)) {
        return controllerFactories.value(name)->create();
    }
    throw new QtException(QString("No such controller: ")+name);
}

PageController *ControllerManager::getPage(const QString &name)
{
    if (this->controllerFactories.contains(name)) {
        PageController * p = dynamic_cast<PageController*>(controllerFactories.value(name)->create());
        if (p != NULL) {
            return p;
        }
    }
    throw new QtException(QString("No such page: ")+name);
}


