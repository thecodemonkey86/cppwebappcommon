#include "htmlautoclosetag.h"

HtmlAutoCloseTag::HtmlAutoCloseTag(const QString &tag)
{
    this->tag = tag;
}

void HtmlAutoCloseTag::setAttribute(const QString &name, const QString &value)
{
    for(uint i=0;i<this->attributes.size();i++) {
        if (this->attributes[i].first == name) {
            this->attributes[i].second = value;
            return;
        }
    }
    this->attributes.push_back(QPair<QString,QString>(name,value));
}

void HtmlAutoCloseTag::render() const
{
    out << '<'
        << tag
        << ' ';
    for(auto it=attributes.cbegin(); it != attributes.cend();++it) {
        out << it->first
            << "=\""
            << it->second.toHtmlEscaped()
            << "\"";
    }


    out << "/>";
}
