#include "abstractpagecontroller.h"



SessionData *AbstractPageController::getSessionData() const
{
    return sessionData;
}

AbstractPageController* AbstractPageController::setSessionData(SessionData *value)
{
    sessionData = value;
    return this;
}

QUrl AbstractPageController::getUrl()
{
    return QUrl("/?controller="+getName());
}

Sql *AbstractPageController::getSql() const
{
    return sql;
}

void AbstractPageController::setSql(Sql *value)
{
    sql = value;
}
AbstractPageController::AbstractPageController()
{
    
}

AbstractPageController::~AbstractPageController()
{
    
}

void AbstractPageController::runController()
{
    auto msg = run();
    msg->setSessionData(sessionData);
    view->update(std::move(msg));
}

AbstractPageController *AbstractPageController::setServerData(ServerData *value)
{
    this->serverData = value;
    return this;
}

AbstractPageController *AbstractPageController::setRequestData(RequestData *value)
{
    this->requestData = value;
    return this;
}




