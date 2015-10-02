#include "pageconfig.h"

PageConfig::PageConfig()
{
//    this->controllerInstance = nullptr;
}

PageConfig::~PageConfig()
{

}

unique_ptr<HtmlTemplate>PageConfig::htmlTemplate(unique_ptr<AbstractTemplate>body)
{
    HtmlTemplate * html = new HtmlTemplate();
    html->setBodyTemplate(move(body));
    return unique_ptr<HtmlTemplate>(html);
}

