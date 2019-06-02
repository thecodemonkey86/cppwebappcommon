#include "multiactionpagecontroller.h"
#include "core/requestdata.h"
#include "exception/qtexception.h"

using namespace QtCommon2;

unique_ptr<ViewData> MultiActionPageController::run()
{
   return nullptr;

}

void MultiActionPageController::runController()
{
    QString action = requestData->getString(QStringLiteral("action"));
    if (actions.contains(action)) {
        auto a = actions.value(action);
        a->setSqlCon(sqlCon);
        a->setServerData(serverData);
        a->setRequestData(requestData);
        a->setSessionData(sessionData);
        a->setHttpHeader(httpHeader);
        a->runAction();
    } else {
        throw QtException("No such action");
    }


}



void MultiActionPageController::setOutStream(FCGX_Stream *outStream)
{
    for(const auto & a : actions) {
        a->setOutStream(outStream);
    }
}
