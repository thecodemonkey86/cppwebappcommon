#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QString>
#include <QMap>
#include "model/beans/session.h"

#include "page_config/pageconfig.h"

class PageManager
{

protected:
     static QMap<QString, PageManager*> instancesPerSession;

     Session*session;
    QMap<QString,PageConfig*> pages;
    PageManager(Session*session);
public:
    static PageManager *getInstance(Session *session);
    static AbstractPageController * getController(const QString &name,Session *session);
    template<class T> static QString getControllerUrl() {
         return QString("/?controller="+T::controllerName());
    }
    template<class C,class A> static QString getActionUrl() {
         return QString("/?controller=")+C::controllerName()+QString("&amp;action=")+A::actionName();
    }

    virtual ~PageManager();
    PageManager* add(PageConfig * cfg) ;
    PageConfig* getCfg(const QString&name);
};

#endif // PAGEMANAGER_H
