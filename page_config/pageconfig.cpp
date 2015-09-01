#include "pageconfig.h"

PageConfig::PageConfig()
{

}

PageConfig::~PageConfig()
{

}

HtmlTemplate *PageConfig::htmlTemplate(AbstractTemplate *body)
{
    HtmlTemplate * html = new HtmlTemplate();
    html->setBodyTemplate(body);
    return html;
}

