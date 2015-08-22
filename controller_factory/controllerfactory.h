#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include <QString>
#include "controller/abstractcontroller.h"
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT ControllerFactory
{

public:
    ControllerFactory();
    virtual ~ControllerFactory();
    virtual AbstractController * create()=0;
    virtual QString controllerName() = 0;
};

#endif // CONTROLLERFACTORY_H

