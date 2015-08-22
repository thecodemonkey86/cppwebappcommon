#include "htmltemplate.h"



HtmlTemplate::HtmlTemplate()
{

}

HtmlTemplate::~HtmlTemplate()
{

}

void HtmlTemplate::render()
{
    renderHeader();
    bodyTemplate->render();
    renderFooter();
}

void HtmlTemplate::outAttr(const QString &attr, const QString &value)
{
    output<<attr<<"=\""<<value<<"\" ";
}

void HtmlTemplate::outBeginTag(const QString &tag)
{
output<<QChar('<');
output<<tag;
output<<QChar('>');
}

void HtmlTemplate::outEndTag(const QString &tag)
{
    output<<QString("</");
    output<<tag;
    output<<QChar('>');
}
AbstractTemplate *HtmlTemplate::getBodyTemplate() const
{
    return this->bodyTemplate;
}

void HtmlTemplate::setBodyTemplate(AbstractTemplate *bodyTemplate)
{
    this->bodyTemplate = bodyTemplate;
}

void HtmlTemplate::renderHeader()
{
    // qDebug()<<"teeets";
   output<<(QString("<!DOCTYPE html>"));
   outBeginTag("head");
   output<<(QString("<meta charset=\"utf-8\">"));
   foreach(QString css, includeCss) {
       output<<("<link ");
       outAttr("rel", "stylesheet");
       outAttr("href", css);
       outAttr("type", "text/css");
       output<<(">");

   }
   outEndTag("head");
   outBeginTag("body");
}

void HtmlTemplate::renderFooter()
{
    outBeginTag("footer");
    foreach(QString js,includeJs) {
       output<<("<script ");
       outAttr("type", "text/javascript");
       outAttr("src", js);
       output<<(">");
    }
    outEndTag("footer");
    outEndTag("body");
    outEndTag("html");
}


