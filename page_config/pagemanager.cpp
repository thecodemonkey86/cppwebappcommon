#include "pagemanager.h"

PageManager::PageManager()
{

}

QString PageManager::getBaseUrl()
{
    return baseUrl;
}

void PageManager::setBaseUrl(const QString &value)
{
    baseUrl = value;
}

void PageManager::runController(const QString&page, RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader *httpHeader, Sql*sqlCon)
{
    if (this->pages.contains(page)) {
        auto cfg = this->pages[page];
        auto ctrl = cfg->createController();
        ctrl->setSessionData(sessionData);
        ctrl->setRequestData(requestData);
        ctrl->setServerData(serverData);
        ctrl->setHttpHeader(httpHeader);
        ctrl->setSql(sqlCon);
        auto tmpl = cfg->getView();
        ctrl->registerView(std::move(tmpl));
        ctrl->runController();
    } else {
        throw QtException(QStringLiteral("page not found: %1").arg(page));
    }
}

//void PageManager::addPage( const shared_ptr<PageConfig> &config)
//{
//    this->pages.insert(config->getName(),config);
//}



QString PageManager::baseUrl ="/";
