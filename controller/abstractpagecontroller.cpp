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
AbstractPageController::AbstractPageController()
{
    
}

AbstractPageController::~AbstractPageController()
{
    
}

void AbstractPageController::runController()
{
    MvcMessage * msg = run();
    view->update(msg);
    if (msg != nullptr)
        delete msg;
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



void AbstractPageController::registerTemplate(AbstractTemplate *view)
{
   HtmlTemplate * html = new HtmlTemplate();
   html->setBodyTemplate(view);
   AbstractController::registerView(html);
}

