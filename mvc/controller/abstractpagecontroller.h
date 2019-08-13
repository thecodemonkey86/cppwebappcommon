#ifndef ABSTRACTPAGECONTROLLER_H
#define ABSTRACTPAGECONTROLLER_H

#include "mvc/model/viewdata.h"
#include "mvc/view/abstractview.h"
#include <memory>
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/sessiondata.h"
#include "core/httpheader.h"
#include <QtSql/QSqlDatabase>
#include "webappcommon_global.h"

using namespace std;

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

    unique_ptr<AbstractView> view;
    virtual unique_ptr<ViewData> run()=0;
public:
    AbstractPageController();
    virtual ~AbstractPageController()=default;

    void registerView(unique_ptr<AbstractView> view);
    template<class T> inline void registerView() {
         this->view = make_unique<T>();
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

#endif // ABSTRACTPAGECONTROLLER_H
