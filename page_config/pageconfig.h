#ifndef PAGECONFIG_H
#define PAGECONFIG_H
#include <QString>
#include "controller/abstractpagecontroller.h"
#include "view/template/abstracttemplate.h"
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT PageConfig
{
//protected:
//    AbstractPageController *controllerInstance;
public:
    PageConfig();
    virtual ~PageConfig();
    virtual unique_ptr<AbstractPageController> getController()=0;
    virtual unique_ptr<AbstractTemplate> getTemplate()=0;
    virtual QString controllerName() = 0;
    virtual unique_ptr<HtmlTemplate> htmlTemplate(unique_ptr<AbstractTemplate>body);
};

#endif // PAGECONFIG_H
