#pragma once


#include "mvc/view/abstractview.h"
#include <mvc/model/viewdata.h>
#include <memory>
class ServerData;
class RequestData;
class SessionData;
class HttpHeader;
struct FCGX_Stream;
#include <QtSql/QSqlDatabase>
#include "webappcommon_global.h"



/**
 * @brief abstract base class for single action page controllers
 */
class WEBAPPCOMMONSHARED_EXPORT AbstractPageController
{
protected:
    RequestData * requestData;
    ServerData * serverData;
    SessionData * sessionData;
    HttpHeader * httpHeader;
    QSqlDatabase sqlCon;

    std::unique_ptr<AbstractView> view;
    virtual std::unique_ptr<ViewData> run()=0;
public:
    AbstractPageController();
    virtual ~AbstractPageController()=default;

    void registerView(std::unique_ptr<AbstractView> view);
    template<class T> inline void registerView() {
         this->view = std::make_unique<T>();
    }
    virtual void runController();


    RequestData *getRequestData() const;
    void setRequestData(RequestData *value);
    ServerData *getServerData() const;
    void setServerData(ServerData *value);
    SessionData *getSessionData() const;
    void setSessionData(SessionData *value);
    QSqlDatabase getSqlCon() const;
    virtual void setSqlCon(const QSqlDatabase &value);
    HttpHeader *getHttpHeader() const;
    void setHttpHeader(HttpHeader *value);
    virtual void setOutStream(FCGX_Stream *outStream);
};

