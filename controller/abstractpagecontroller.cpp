#include "pagecontroller.h"


PageController::PageController()
{

}

PageController::~PageController()
{

}

PageController *PageController::setServerData(ServerData *value)
{
    this->serverData = value;
    return this;
}

PageController *PageController::setRequestData(RequestData *value)
{
    this->requestData = value;
    return this;
}



void PageController::registerTemplate(AbstractTemplate *view)
{
   HtmlTemplate * html = new HtmlTemplate();
   html->setBodyTemplate(view);
   AbstractController::registerView(html);
}

