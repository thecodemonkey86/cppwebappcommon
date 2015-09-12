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
AbstractPageController::AbstractPageController()
{
    
}

AbstractPageController::~AbstractPageController()
{
    
}

void AbstractPageController::runController()
{
    unique_ptr<MvcMessage> msg = run();
    if (msg  != nullptr) {
        msg->setSessionData(sessionData);
        view->update(move(msg));
    }
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



void AbstractPageController::registerTemplate(unique_ptr<AbstractTemplate>view)
{
   unique_ptr<HtmlTemplate > html(new HtmlTemplate());
   html->setBodyTemplate(move(view));
   AbstractController::registerView(shared_ptr<HtmlTemplate> (move(html)));
}

