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
    template<class T> void addPage(const shared_ptr<T> &config) {
        pages.insert(T::name(),config);
    }
    template<class T> static QString getPageUrl() {
         return QStringLiteral("/?page=%1").arg(T::name());
    }
    template<class T> static QString getPageUrl(const QVector<QPair<QString,QString>>args) {
         QString url = QStringLiteral("/?page=%1").arg(T::name());
         for(const QPair<QString,QString> & a : args) {
            url += QStringLiteral("&%1=%2").arg(a.first, a.second);
         }
         return url;
    }
    template<class T> static QString getPageUrl(const QString&action) {
         return QStringLiteral("/?page=%1&action=%2").arg(T::name(),action);
    }
    static QString getBaseUrl();
    static void setBaseUrl(const QString &value);
};

#endif // PAGEMANAGER_H
