#include "multiactioncontroller.h"
#include "core/requestdata.h"
#include "exception/qtexception.h"

MultiActionController::MultiActionController()
{

}

MultiActionController::~MultiActionController()
{

}

unique_ptr<MvcMessage> MultiActionController::run()
{
    if (actions.contains(requestData->getString(QStringLiteral("action")))) {
        auto a = actions.value(requestData->getString(QStringLiteral("action")));
        a->setSql(sql);
        a->setServerData(serverData);
        a->setRequestData(requestData);
        a->setSessionData(sessionData);
        a->setHttpHeader(httpHeader);
        return a->run();
    } else {
        throw QtException("No such action");
    }

}


