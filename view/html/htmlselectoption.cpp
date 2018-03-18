#include "htmlselectoption.h"


HtmlSelectOption::HtmlSelectOption(const QString &value, const QString &display) : HtmlTag("option")
{
    attributes.push_back(QPair<QString,QString>("value",value));
    this->display = display;
}


void HtmlSelectOption::renderChildren() const
{
    FastCgiCout::write(display.toHtmlEscaped());
}
