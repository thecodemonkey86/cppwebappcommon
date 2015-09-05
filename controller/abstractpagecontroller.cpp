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
    MvcMessage * msg = run();
    if (msg  != nullptr) {
        msg->setSessionData(sessionData);
        view->update(msg);
        delete msg;
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



void AbstractPageController::registerTemplate(AbstractTemplate *view)
{
   HtmlTemplate * html = new HtmlTemplate();
   html->setBodyTemplate(view);
   AbstractController::registerView(html);
}

