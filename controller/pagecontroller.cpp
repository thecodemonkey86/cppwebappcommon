#include "pagecontroller.h"


PageController::PageController()
{

}

PageController::~PageController()
{

}

void PageController::registerTemplate(AbstractTemplate *view)
{
   HtmlTemplate * html = new HtmlTemplate();
   html->setBodyTemplate(view);
   AbstractController::registerView(html);
}
