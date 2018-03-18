#ifndef PAGECONFIG_H
#define PAGECONFIG_H
#include <QString>
#include "controller/abstractpagecontroller.h"
#include "webappcommon_global.h"
#include <memory>
#include <vector>
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT PageConfig
{


public:
    PageConfig();
    virtual ~PageConfig();
    virtual unique_ptr<AbstractPageController> createController()=0;
    virtual unique_ptr<AbstractView> getView()=0;
    virtual QString controllerName() = 0;

};

#endif // PAGECONFIG_H
