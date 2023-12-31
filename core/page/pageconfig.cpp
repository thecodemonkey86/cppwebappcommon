#include "pageconfig.h"
#include <mvc/controller/abstractpagecontroller.h>
void PageConfig::run(RequestData * requestData,
                     SessionData * sessionData,
                     ServerData * serverData,
                     HttpHeader * httpHeader,
                     const QSqlDatabase & sqlCon,
                     FCGX_Stream *outStream)
{
   auto ctrl = createController();
   ctrl->setOutStream(outStream);
   ctrl->setRequestData(requestData);
   ctrl->setServerData(serverData);
   ctrl->setSessionData(sessionData);
   ctrl->setHttpHeader(httpHeader);
   ctrl->setSqlCon(sqlCon);
   ctrl->runController();
}

