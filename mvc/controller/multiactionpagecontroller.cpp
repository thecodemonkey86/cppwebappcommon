#include "multiactionpagecontroller.h"
#include "core/requestdata.h"
#include "exception/qtexception.h"

using namespace QtCommon2;

std::unique_ptr<ViewData> MultiActionPageController::run()
{
   return nullptr;

}

void MultiActionPageController::runController()
{
  QString pAction("action");
  if(requestData->isGetParamSet(pAction)){
    QString action = requestData->getStringNoCheckForExistance(pAction);
    if (actions.contains(action)) {
      auto a = actions.value(action);
      a->setSessionData(sessionData);
      a->setSqlCon(sqlCon);
      a->setServerData(serverData);
      a->setRequestData(requestData);     
      a->setHttpHeader(httpHeader);
      a->runAction();
    } else if(defaultAction != nullptr) {
      defaultAction->setSessionData(sessionData);
      defaultAction->setSqlCon(sqlCon);
      defaultAction->setServerData(serverData);
      defaultAction->setRequestData(requestData);      
      defaultAction->setHttpHeader(httpHeader);
      defaultAction->runAction();
    } else {
      throw QtException(QLatin1String("No such action"));
    }
  } else if(defaultAction != nullptr) {
    defaultAction->setSessionData(sessionData);
     defaultAction->setSqlCon(sqlCon);
    defaultAction->setServerData(serverData);
    defaultAction->setRequestData(requestData);    
    defaultAction->setHttpHeader(httpHeader);
    defaultAction->runAction();
  } else {
    throw QtException(QLatin1String("No such action"));
  }


}



void MultiActionPageController::setOutStream(FCGX_Stream *outStream)
{
    for(const auto & a : actions) {
        a->setOutStream(outStream);
    }
}
