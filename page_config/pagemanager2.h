#ifndef PAGEMANAGER2_H
#define PAGEMANAGER2_H
#include <QString>
#include <memory>
#include <vector>
#include "exception/qtexception.h"
#include <QHash>

using namespace std;
#include "page_config/pageconfig.h"

class PageManager2
{
private:
    QHash<QString,shared_ptr<PageConfig>> pages;

public:
    PageManager2();
    static QString getControllerUrl(const QString&name);
    void runController(const QString&name, RequestData * requestData, SessionData * sessionData, ServerData * serverData, Sql*sqlCon);
    void addPage(const QString& name,const shared_ptr<PageConfig> &config);
    template<class T> static QString getControllerUrl() {
         return QString("/?controller="+T::controllerName());
    }
};

#endif // PAGEMANAGER2_H
