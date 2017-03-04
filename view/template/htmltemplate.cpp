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
   output<<"<!DOCTYPE html>";
   outBeginTag(QStringLiteral("html"));
   outBeginTag(QStringLiteral("head"));
   outBeginTagWithAttrs(QStringLiteral("base"));
   outAttr(QStringLiteral("href"), baseUrl);
   output << '>';

   outBeginTagWithAttrs(QStringLiteral("meta"));
   outAttr(QStringLiteral("charset"), QStringLiteral("utf-8"));
   output << '>';
   for(const QString &css: includeCss) {
       outBeginTagWithAttrs(QStringLiteral("link"));
       outAttr(QStringLiteral("rel"), QStringLiteral("stylesheet"));
       outAttr(QStringLiteral("href"), QStringLiteral("/css/")+ css);
       outAttr(QStringLiteral("type"), QStringLiteral("text/css"));
       outAttr(QStringLiteral("media"), QStringLiteral("screen"));
       output << '>';

   }
   outBeginTagWithAttrs(QStringLiteral("style"));
   outAttr(QStringLiteral("type"), QStringLiteral("text/css"));
   output << '>';
   renderInlineCss();
   outEndTag(QStringLiteral("style"));


   outEndTag(QStringLiteral("head"));
   outBeginTag(QStringLiteral("body"));
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
