#include "pagemanager2.h"

PageManager2::PageManager2()
{

}

QString PageManager2::getBaseUrl()
{
    return baseUrl;
}

void PageManager2::setBaseUrl(const QString &value)
{
    baseUrl = value;
}

void PageManager2::runController(const QString&name, RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader *httpHeader, Sql*sqlCon)
{
    if (this->pages.contains(name)) {
        auto cfg = this->pages[name];
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
        throw QtException(QStringLiteral("page not found: %1").arg(name));
    }
}

void PageManager2::addPage( const shared_ptr<PageConfig> &config)
{
    this->pages.insert(config->controllerName(),config);
}



QString PageManager2::baseUrl ="/";
