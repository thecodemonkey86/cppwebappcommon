#include "htmltemplate.h"



void HtmlTemplate::update(unique_ptr<MvcMessage> updateMsg)
{
    render();
}


void HtmlTemplate::outAttr(const QString &attr, const QString &value)
{
    output<<' '<<attr<<"=\""<<value<<"\" ";
}

void HtmlTemplate::outBeginTag(const QString &tag)
{
output<<QChar('<');
output<<tag;
output<<QChar('>');
}

void HtmlTemplate::outBeginTagWithAttrs(const QString &tag)
{
output<<QChar('<');
output<<tag;
}


void HtmlTemplate::outEndTag(const QString &tag)
{
    output<<QString("</");
    output<<tag;
    output<<QChar('>');
}


void HtmlTemplate::render()
{
    renderHeader();
    renderBody();
    renderFooter();
}




void HtmlTemplate::renderHeader()
{
    // qDebug()<<"teeets";
   output<<(QString("<!DOCTYPE html>"));
   outBeginTag("html");
   outBeginTag("head");
   outBeginTagWithAttrs("base");
   outAttr("href", baseUrl);
   output<<('>');

   outBeginTagWithAttrs("meta");
   outAttr("charset", "utf-8");
   output << '>';
   for(const QString &css: includeCss) {
       outBeginTagWithAttrs("link");
       outAttr("rel", "stylesheet");
       outAttr("href", "/css/"+ css);
       outAttr("type", "text/css");
       outAttr("media", "screen");
       output << '>';

   }
   outBeginTagWithAttrs("style");
   outAttr("type", "text/css");
   output << '>';
   renderInlineCss();
   outEndTag("style");


   outEndTag("head");
   outBeginTag("body");
}

void HtmlTemplate::renderFooter()
{
    outBeginTag("footer");
    outBeginTagWithAttrs("script");
    outAttr("type", "text/javascript");
    output<<('>');
     renderInlineJs();
    outEndTag("script");

    for(const QString &js: includeJs) {
       outBeginTagWithAttrs("script");
       outAttr("type", "text/javascript");
       outAttr("src", "/js/"+ js);
       output<<('>');
       outEndTag("script");
    }
    outEndTag("footer");
    outEndTag("body");
    outEndTag("html");
}

void HtmlTemplate::renderInlineJs()
{

}

void HtmlTemplate::renderInlineCss()
{

}

QString HtmlTemplate::getBaseUrl() const
{
    return baseUrl;
}

void HtmlTemplate::setBaseUrl(const QString &value)
{
    baseUrl = value;
}




QString HtmlTemplate::getHttpContentType()
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

FastCgiCout HtmlTemplate::output;
