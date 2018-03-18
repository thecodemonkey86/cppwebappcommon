#include "htmltext.h"

HtmlText::HtmlText(const QString &content)
{
    this->content = content;
}


void HtmlText::render() const
{
    FastCgiCout::write(content.toHtmlEscaped());
}
