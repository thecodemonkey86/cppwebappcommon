#include "abstractpagecontroller.h"


AbstractPageController::AbstractPageController()
{

}

AbstractPageController::~AbstractPageController()
{

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

