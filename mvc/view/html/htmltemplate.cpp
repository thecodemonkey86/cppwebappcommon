#include "htmltemplate.h"
#include "core/page/pagemanager.h"
#include "core/httpheader.h"
#include <QStringList>

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
   //outBeginTagWithAttrs("base");
  // outAttr("href", getBaseUrl());
  // output('>');

   outBeginTagWithAttrs("meta");
   outAttr("charset", "utf-8");
   output('>');
   outBeginTagWithAttrs("meta");
   outAttr("viewport", "width=device-width, initial-scale=1, shrink-to-fit=no");
   output('>');
   for(const QString &css: includeCss) {
       outBeginTagWithAttrs("link");
       outAttr("rel", "stylesheet");
       outAttr("href", css);
       outAttr("type", "text/css");
       outAttr("media", "screen");
       output('>');

   }

   for(const QString &font: includeFonts) {
       outBeginTagWithAttrs("link");
       outAttr("href", font);
       outAttr("rel", "stylesheet");
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
    for(const QString &js: includeJs) {
       outBeginTagWithAttrs("script");
       outAttr("type", "text/javascript");
       outAttr("src", js);
       output('>');
       outEndTag("script");
    }
    outBeginTagWithAttrs("script");
    outAttr("type", "text/javascript");
    output('>');
     renderInlineJs();
    outEndTag("script");


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

//QString HtmlTemplate::getBaseUrl() const
//{
//    return PageManager::getBaseUrl();
//}




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

void HtmlTemplate::addFont(const QString &font)
{
    includeFonts.append(font);
}

