#pragma once

class MultiActionPageController;
class ServerData;
class RequestData;
class SessionData;
class HttpHeader;
#include <QSqlDatabase>
#include "webappcommon_global.h"
#include "mvc/view/abstractview.h"
#include <mvc/model/viewdata.h>
class WEBAPPCOMMONSHARED_EXPORT AbstractAction
{
protected:
    std::unique_ptr<AbstractView> view;
    ServerData * serverData;
     RequestData * requestData;
     SessionData * sessionData;
     HttpHeader * httpHeader;
    QSqlDatabase sqlCon;
    virtual std::unique_ptr<ViewData> run()=0;
public:
    AbstractAction() = default;
    virtual ~AbstractAction() = default;
    void runAction();
    void setServerData(ServerData *value);
    void setRequestData(RequestData *value);
    void setSessionData(SessionData *value);
    void setHttpHeader(HttpHeader *value);
    QSqlDatabase getSqlCon() const;
    void setSqlCon(const QSqlDatabase &value);
    QString getName() const;
    void setOutStream(FCGX_Stream *outStream);
    void registerView(std::unique_ptr<AbstractView> view);
    template<class T> void registerView()
    {
        this->registerView(std::make_unique<T>());
    }
};

