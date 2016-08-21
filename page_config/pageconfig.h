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
protected:
    QStringList cssFiles,jsFiles;

public:
    PageConfig();
    virtual ~PageConfig();
    virtual unique_ptr<AbstractPageController> createController()=0;
    virtual unique_ptr<HtmlTemplate> getTemplate()=0;
    virtual QString controllerName() = 0;
    void addCssFile(const  QString & cssFile);
    void addJsFile(const  QString & jsFile);
    QStringList getCssFiles() const;
    QStringList getJsFiles() const;
};

#endif // PAGECONFIG_H
