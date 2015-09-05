#include "pagemanager.h"
#include "exception/qtexception.h"

PageManager::PageManager(Session*session)
{
    this->session = session;
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

PageManager *PageManager::getInstance(Session *session)
{
    if (!instancesPerSession.contains(session->getId())) {
        PageManager * instance = new PageManager(session);
        instancesPerSession.insert(session->getId(),instance);
        return instance;
    }
    return instancesPerSession.value(session->getId());
}

AbstractPageController *PageManager::getController(const QString &name, Session *session)
{
    return getInstance(session)->getCfg(name)->getController();
}

QMap<QString, PageManager*> PageManager::instancesPerSession;


