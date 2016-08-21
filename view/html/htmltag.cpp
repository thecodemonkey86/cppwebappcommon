#include "htmltag.h"

HtmlTag::HtmlTag(const QString &tag)
{
    this->tag = tag;
}

void HtmlTag::setAttribute(const QString &name, const QString &value)
{
    for(uint i=0;i<this->attributes.size();i++) {
        if (this->attributes[i].first == name) {
            this->attributes[i].second = value;
            return;
        }
    }
    this->attributes.push_back(QPair<QString,QString>(name,value));
}

void HtmlTag::addClass(const QString &cls)
{
    this->classes.push_back(cls);
}

void HtmlTag::render() const
{
    out << '<'
        << tag << ' ';
    for(auto it=attributes.cbegin(); it != attributes.cend();++it) {
        out << it->first
            << "=\""
            << it->second.toHtmlEscaped()
            << "\" ";
    }


    if (classes.size()>0) {
        out << " class=\"";
        for(uint i=0;i<classes.size()-1;i++) {
            out << classes[i].toHtmlEscaped();
            out << ' ';
        }
        out << classes.back().toHtmlEscaped();
        out << '"';
    }

    out << '>';

   renderChildren();

    out << "</"<< tag << '>';
}
