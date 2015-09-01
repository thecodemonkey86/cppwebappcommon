#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QString>
#include <QMap>

#include "util/singleton.h"
#include "page_config/pageconfig.h"

class PageManager : public Singleton<PageManager>
{
    friend class Singleton<PageManager>;
protected:
    QMap<QString,PageConfig*> pages;
    PageManager();
public:
    virtual ~PageManager();
    PageManager* add(PageConfig * cfg) ;
    PageConfig* getCfg(const QString&name);
};

#endif // PAGEMANAGER_H
