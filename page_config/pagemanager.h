#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H
#include <QString>
#include <QPair>
#include <memory>
#include <vector>
#include "exception/qtexception.h"
#include <QHash>
#include "webappcommon_global.h"

using namespace std;
#include "page_config/pageconfig.h"

class WEBAPPCOMMONSHARED_EXPORT PageManager
{
private:
    QHash<QString,shared_ptr<PageConfig>> pages;


public:
  PageManager();
 //   static QString getControllerUrl(const QString&name);
    static QString baseUrl;
    void runController(const QString&page, RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader * httpHeader, Sql*sqlCon);
    template<class Controller> void addPage(const shared_ptr<Controller> &config) {
        pages.insert(Controller::name(),config);
    }
    template<class Controller> static QString url() {
         return QStringLiteral("/?page=%1").arg(Controller::name());
    }
    template<class Controller> static QString url(const QVector<QPair<QString,QString>>& args) {
         QString url = QStringLiteral("/?page=%1").arg(Controller::name());
         for(const QPair<QString,QString> & a : args) {
            url += QStringLiteral("&%1=%2").arg(a.first, a.second);
         }
         return url;
    }
    template<class Controller> static QString url(const QPair<QString,QString> & arg) {
         return QStringLiteral("/?page=%1&%2=%3").arg(Controller::name(),arg.first, arg.second);
    }
    template<class Controller> static QString url(const QString&action) {
         return QStringLiteral("/?page=%1&action=%2").arg(Controller::name(),action);
    }
    template<class Controller,class Action> static QString url() {
         return QStringLiteral("/?page=%1&action=%2").arg(Controller::name(),Action::name());
    }
    static QString getBaseUrl();
    static void setBaseUrl(const QString &value);
};

#endif // PAGEMANAGER_H
