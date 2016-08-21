#include "pageconfig.h"

QStringList PageConfig::getCssFiles() const
{
    return cssFiles;
}

QStringList PageConfig::getJsFiles() const
{
    return jsFiles;
}

PageConfig::PageConfig()
{
    //    this->controllerInstance = nullptr;
}

PageConfig::~PageConfig()
{

}

void PageConfig::addCssFile(const QString &cssFile)
{
    this->cssFiles.append(cssFile);
}

void PageConfig::addJsFile(const QString &jsFile)
{
    this->jsFiles.append(jsFile);
}

//unique_ptr<HtmlTemplate>PageConfig::htmlTemplate(unique_ptr<AbstractTemplate>body)
//{
//    HtmlTemplate * html = new HtmlTemplate();
//    html->setBodyTemplate(move(body));
//    return unique_ptr<HtmlTemplate>(html);
//}

