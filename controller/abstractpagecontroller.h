#ifndef ABSTRACTPAGECONTROLLER_H
#define ABSTRACTPAGECONTROLLER_H

#include "controller/abstractcontroller.h"
#include "view/template/htmltemplate.h"

#include "core/serverdata.h"
#include "core/requestdata.h"
#include "core/sessiondata.h"
#include <QSqlDatabase>
#include <memory>
#include "webappcommon_global.h"
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT AbstractPageController : public AbstractController
{
protected:
    ServerData * serverData;
     RequestData * requestData;
     SessionData * sessionData;
     HttpHeader *  httpHeader;
     QSqlDatabase sql;
     virtual unique_ptr<MvcMessage> run()=0;
public:
    AbstractPageController();
    virtual ~AbstractPageController();

    virtual void runController();

//    virtual void registerTemplate(unique_ptr<AbstractTemplate>view);
    virtual void setServerData(ServerData *value);
    virtual void setRequestData(RequestData *value);
    virtual void setSessionData(SessionData *value);
     virtual void setHttpHeader(HttpHeader *  httpHeader);
    SessionData *getSessionData() const;
//    virtual QUrl getUrl();
//    virtual QUrl getUrl(const QString&action);

    QSqlDatabase getSql() const;
    void setSql(const QSqlDatabase &value);
};

#endif // ABSTRACTPAGECONTROLLER_H
