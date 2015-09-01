#include "pagemanager.h"
#include "exception/qtexception.h"

PageManager::PageManager()
{

}

PageManager::~PageManager()
{

}

PageManager* PageManager::add(PageConfig *cfg)
{
    pages.insert(cfg->controllerName(), cfg);
    return this;
}

PageConfig* PageManager::getCfg(const QString &name)
{
    if (pages.contains(name)) {
        return pages.value(name);
    } else {
        throw new QtException("no such page");
    }
}

