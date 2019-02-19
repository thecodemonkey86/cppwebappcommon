#include "htmltemplate.h"
#include "page_config/pagemanager.h"
#ifndef output
#define output FastCgiCout::write
#endif

void HtmlTemplate::outAttr(const QString &attr, const QString &value) const
{
    output(' ');
    output(attr);
    output("=\"");
    output(value);
    output("\" ");
}

void HtmlTemplate::outBeginTag(const QString &tag) const
{
output('<');
output(tag);
output('>');
}

void HtmlTemplate::outBeginTagWithAttrs(const QString &tag) const
{
output('<');
output(tag);
}


void HtmlTemplate::outEndTag(const QString &tag) const
{
    output("</");
    output(tag);
    output('>');
}




void HtmlTemplate::renderHeader() const
{
   output("<!DOCTYPE html>");
   outBeginTag("html");
   outBeginTag("head");
   outBeginTagWithAttrs("base");
   outAttr("href", getBaseUrl());
   output('>');

   outBeginTagWithAttrs("meta");
   outAttr("charset", "utf-8");
   output('>');
   for(const QString &css: includeCss) {
       outBeginTagWithAttrs("link");
       outAttr("rel", "stylesheet");
       outAttr("href", css);
       outAttr("type", "text/css");
       outAttr("media", "screen");
       output('>');

   }
   outBeginTagWithAttrs("style");
   outAttr("type", "text/css");
   output('>');
   renderInlineCss();
   outEndTag("style");


   outEndTag("head");
   outBeginTag("body");
}

void HtmlTemplate::renderFooter() const
{
    outBeginTag("footer");
    outBeginTagWithAttrs("script");
    outAttr("type", "text/javascript");
    output('>');
     renderInlineJs();
    outEndTag("script");

    for(const QString &js: includeJs) {
       outBeginTagWithAttrs("script");
       outAttr("type", "text/javascript");
       outAttr("src", js);
       output('>');
       outEndTag("script");
    }
    outEndTag("footer");
    outEndTag("body");
    outEndTag("html");
}

void HtmlTemplate::renderInlineJs() const
{

}

void HtmlTemplate::renderInlineCss() const
{

}

QString HtmlTemplate::getBaseUrl() const
{
    return PageManager::getBaseUrl();
}




QString HtmlTemplate::getHttpContentType() const
{
    return HttpHeader::CONTENT_TYPE_TEXT_HTML;
}

void HtmlTemplate::addCssFiles(const QStringList &cssFiles)
{
    for(const QString&c:cssFiles)
        this->includeCss.append(c);
}

void HtmlTemplate::addJsFiles(const QStringList &jsFiles)
{
    for(const QString&c:jsFiles)
        this->includeJs.append(c);
}

void HtmlTemplate::addCssFile(const QString &cssFile)
{
    includeCss.append(cssFile);
}

void HtmlTemplate::addJsFile(const QString &jssFile)
{
    includeJs.append(jssFile);
}

