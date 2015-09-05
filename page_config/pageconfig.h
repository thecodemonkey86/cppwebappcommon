#ifndef PAGECONFIG_H
#define PAGECONFIG_H
#include <QString>
#include "controller/abstractpagecontroller.h"
#include "view/template/abstracttemplate.h"
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT PageConfig
{
protected:
    AbstractPageController *controllerInstance;
public:
    PageConfig();
    virtual ~PageConfig();
    virtual AbstractPageController * getController()=0;
    virtual AbstractTemplate * getTemplate()=0;
    virtual QString controllerName() = 0;
    virtual HtmlTemplate* htmlTemplate(AbstractTemplate*body);
};

#endif // PAGECONFIG_H
