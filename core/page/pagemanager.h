#pragma once

#include <QString>
#include <QHash>
#include <QUrl>
#include <memory>
#include "core/requestparam.h"
#include "webappcommon_global.h"
class RequestData;
class ServerData;
class SessionData;
class HttpHeader;
class QSqlDatabase;
struct FCGX_Stream;
class RequestParam;
class PageConfig;

class WEBAPPCOMMONSHARED_EXPORT PageManager
{
private:
    QHash<QString,std::shared_ptr<PageConfig>> pages;


public:
    PageManager() = default;
    void runController(const QString&page,FCGX_Stream * outStream,  RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader * httpHeader, const QSqlDatabase & sqlCon);

    /**
     * @brief hasPageForPath
     * @param path normalized path, that MUST start with a slash and MUST NOT end with a slash
     * @return
     */
    bool hasPageForPath(const QString & path) const;

    template<class C> void addPage(const std::shared_ptr<C> &config) {
        pages.insert(C::path(),config);
    }
    template<class C> void addPage() {
        pages.insert(C::path(),std::make_shared<C>());
    }
    template<class C> static QString url() {
        // return QStringLiteral("/?page=%1").arg(C::path());
        return C::path();
    }

    template<class C> static QString url(const std::initializer_list<GetParam>& args) {
        QString url = QStringLiteral("%1/?").arg(C::path());
        if(args.size() > 0)
        {
            auto it = args.begin();
            url += QStringLiteral("%1=%2").arg(it->getName(),it->getPercentEscapedValue());
            ++it;
            while(it != args.end())
            {
                url += QStringLiteral("&%1=%2").arg(it->getName(),it->getPercentEscapedValue());
                ++it;
            }


        }
        return url;
    }

    template<class C> static QString url(const QVector<RequestParam>& args) {
        QString url = QStringLiteral("%1/?").arg(C::path());
        if(args.size() > 0)
        {
            url += QStringLiteral("%1=%2").arg(args[0].getName(),args[0].getPercentEscapedValue());

            for(int i = 1; i < args.size(); i++) {
                url += QStringLiteral("&%1=%2").arg(args[i].getName(),args[i].getPercentEscapedValue());
            }
        }
        return url;
    }
    template<class C> static QString url(const RequestParam & arg) {
        return QStringLiteral("%1/?%2=%3").arg(C::path(),arg.getName(), arg.getPercentEscapedValue());
    }
    template<class C> static QString url(const QString&action) {
        return QStringLiteral("%1/?action=%2").arg(C::path(),action);
    }
    template<class C,class A> static QString url() {
        return QStringLiteral("%1/?action=%2").arg(C::path(),A::name());
    }
    template<class C,class A> static QString url(const RequestParam & arg) {
        return QStringLiteral("%1/?action=%2&%3=%4").arg(C::path(),A::name(),arg.getName(), arg.getPercentEscapedValue());
    }

    template<class C,class A> static QString url(const std::initializer_list<GetParam>& args) {
        QString url = QStringLiteral("%1/?action=%2").arg(C::path(),A::name());
        if(args.size() > 0)
        {
            for(const auto & a : args)
            {
                 url += QStringLiteral("&%1=%2").arg(a.getName(),a.getPercentEscapedValue());
            }

        }
        return url;
    }

    template<class C,class A> static QString url(const QVector<GetParam>& args) {
        QString url = QStringLiteral("%1/?action=%2").arg(C::path(),A::name());
        if(args.size() > 0)
        {
            for(const auto & a : args)
            {
                 url += QStringLiteral("&%1=%2").arg(a.getName(),a.getPercentEscapedValue());
            }

        }
        return url;
    }

    static QString url(QUrl currentUrl, const RequestParam & addOrUpdateParam);
};

