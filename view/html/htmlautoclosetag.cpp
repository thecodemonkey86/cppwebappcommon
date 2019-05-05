#include "htmlautoclosetag.h"

HtmlAutoCloseTag::HtmlAutoCloseTag(const QString &tag)
{
    this->tag = tag;
}

void HtmlAutoCloseTag::setAttribute(const QString &name, const QString &value)
{
    for(int i=0;i<this->attributes.size();i++) {
        if (this->attributes[i].first == name) {
            this->attributes[i].second = value;
            return;
        }
    }
    this->attributes.push_back(QPair<QString,QString>(name,value));
}

void HtmlAutoCloseTag::render() const
{
    output('<');
    output( tag);
    output( ' ');;
    for(const QPair<QString,QString> & attr : this->attributes) {
        output(attr.first);
        output( "=\"");
        output( attr.second.toHtmlEscaped());
        output( "\"");
    }


    output("/>");
}
