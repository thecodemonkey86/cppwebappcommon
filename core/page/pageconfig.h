#ifndef PAGECONFIG_H
#define PAGECONFIG_H

#include "mvc/controller/abstractpagecontroller.h"
#include "mvc/view/abstractview.h"
class PageConfig
{
public:
    PageConfig()  = default;
    virtual ~PageConfig() = default;
    virtual unique_ptr<AbstractPageController> createController()=0;
    void run(RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader * httpHeader, const QSqlDatabase & sqlCon, FCGX_Stream *outStream);
};

#endif // PAGECONFIG_H
