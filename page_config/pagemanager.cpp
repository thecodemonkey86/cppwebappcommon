#include "pagemanager.h"
#include "exception/qtexception.h"

PageManager::PageManager(Session*session)
{
    this->session = session;
}

PageManager::~PageManager()
{

}

PageManager* PageManager::add(const shared_ptr<PageConfig> &cfg)
{
    pages.insert(cfg->controllerName(), cfg);
    return this;
}

shared_ptr<PageConfig> PageManager::getCfg(const QString &name)
{
    if (pages.contains(name)) {
        return pages.value(name);
    } else {
        throw QtException("no such page");
    }
}

shared_ptr<PageManager> PageManager::getInstance(Session *session)
{
    if (!instancesPerSession.contains(session->getId())) {
        shared_ptr<PageManager> instance = make_shared<PageManager>(session);
        instancesPerSession.insert(session->getId(),instance);
        return instance;
    }
    return instancesPerSession.value(session->getId());
}

unique_ptr<AbstractPageController> PageManager::getController(const QString &name, Session *session)
{
    return getInstance(session)->getCfg(name)->getController();
}

QHash<QString, shared_ptr<PageManager>> PageManager::instancesPerSession;


