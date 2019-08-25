#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H
#include <QString>
#include <memory>
#include <vector>
#include "exception/qtexception.h"
#include <QHash>
#include "pageconfig.h"
#include "webappcommon_global.h"
#include "core/requestparam.h"

using namespace std;

class WEBAPPCOMMONSHARED_EXPORT PageManager
{
private:
    QHash<QString,shared_ptr<PageConfig>> pages;


public:
  PageManager() = default;
    void runController(const QString&page,FCGX_Stream * outStream,  RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader * httpHeader, const QSqlDatabase & sqlCon);
    template<class C> void addPage(const shared_ptr<C> &config) {
        pages.insert(C::name(),config);
    }
    template<class C> void addPage() {
        pages.insert(C::name(),make_shared<C>());
    }
    template<class C> static QString url() {
         return QStringLiteral("/?page=%1").arg(C::name());
    }

    template<class C> static QString url(const QVector<RequestParam>& args) {
         QString url = QStringLiteral("/?page=%1").arg(C::name());
         for(const RequestParam & a : args) {
            url += QStringLiteral("&%1=%2").arg(a.toString());
         }
         return url;
    }
    template<class C> static QString url(const RequestParam & arg) {
         return QStringLiteral("/?page=%1&%2=%3").arg(C::name(),arg.getName(), arg.getValue());
    }
    template<class C> static QString url(const QString&action) {
         return QStringLiteral("/?page=%1&action=%2").arg(C::name(),action);
    }
    template<class C,class A> static QString url() {
         return QStringLiteral("/?page=%1&action=%2").arg(C::name(),A::name());
    }
    template<class C,class A> static QString url(const RequestParam & arg) {
      return QStringLiteral("/?page=%1&action=%2&%3=%4").arg(C::name(),A::name(),arg.getName(), arg.getValue());
    }
};

#endif // PAGEMANAGER_H
