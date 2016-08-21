#include "pagemanager2.h"

PageManager2::PageManager2()
{

}

void PageManager2::runController(const QString&name, RequestData * requestData, SessionData * sessionData, ServerData * serverData, Sql*sqlCon)
{
    if (this->pages.contains(name)) {
        auto cfg = this->pages[name];
        auto ctrl = cfg->createController();
        ctrl->setSessionData(sessionData);
        ctrl->setRequestData(requestData);
        ctrl->setServerData(serverData);
        ctrl->setSql(sqlCon);
        auto tmpl = cfg->getTemplate();
        tmpl->addCssFiles(cfg->getCssFiles());
        tmpl->addJsFiles(cfg->getJsFiles());
        cout << "Content-Type: " << tmpl->getHttpContentType().toUtf8().data()<<"\r\n\r\n";
        ctrl->registerView(std::move(tmpl));
        ctrl->runController();
    } else {
        throw QtException("page not found");
    }


//        auto controller = P.createController();
//        ->runController();
}

//QString PageManager2::getControllerUrl(const QString &name)
//{
    //return this->pages[qHash(name)].getController()->getUrl();
//}

void PageManager2::addPage(const QString &name, const shared_ptr<PageConfig> &config)
{
    this->pages.insert(name,config);
}

//void PageManager2::addPage(const QString &name, const shared_ptr<PageConfig> &config)
//{
//    this->pages.insert(name,config);
//}

//shared_ptr<PageConfig> PageManager2::getCfg(const QString &name)
//{
//    if (!this->pages.contains(name)) {
//        throw QtException("page not found");
//    }
//    return this->pages[name];
//}

