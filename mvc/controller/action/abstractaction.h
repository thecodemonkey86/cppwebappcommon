#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H
class MultiActionPageController;
#include "../multiactionpagecontroller.h"
#include "mvc/view/abstractview.h"
#include <QUrl>
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/sessiondata.h"
#include "webappcommon_global.h"
#include <memory>
#include <QtSql/QSqlDatabase>
using namespace std;

class MultiActionPageController;

class WEBAPPCOMMONSHARED_EXPORT AbstractAction
{
protected:
    unique_ptr<AbstractView> view;
    ServerData * serverData;
     RequestData * requestData;
     SessionData * sessionData;
     HttpHeader * httpHeader;
    QSqlDatabase sqlCon;
    virtual unique_ptr<ViewData> run()=0;
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
    inline void registerView(unique_ptr<AbstractView> view);
    template<class T> void registerView()
    {
        this->registerView(make_unique<T>());
    }
};

#endif // ABSTRACTACTION_H
