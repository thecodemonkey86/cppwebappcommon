#include "htmltag.h"

HtmlTag::HtmlTag(const QString &tag)
{
    this->tag = tag;
}

void HtmlTag::setAttribute(const QString &name, const QString &value)
{
    for(int i=0;i<this->attributes.size();i++) {
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
    FastCgiCout::write('<');
    FastCgiCout::write(tag);
    FastCgiCout::write(' ');
    for(const QPair<QString,QString> & attr : this->attributes) {
        FastCgiCout::write(attr.first);
        FastCgiCout::write("=\"");
        FastCgiCout::write(attr.second.toHtmlEscaped());
        FastCgiCout::write("\" ");
    }


    if (classes.size()>0) {
        FastCgiCout::write(" class=\"");
        for(int i=0;i<classes.size()-1;i++) {
            FastCgiCout::write(classes[i].toHtmlEscaped());
            FastCgiCout::write(' ');
        }
        FastCgiCout::write(classes.last().toHtmlEscaped());
        FastCgiCout::write('"');
    }

    FastCgiCout::write('>');

    renderChildren();

    FastCgiCout::write("</");
    FastCgiCout::write(tag);
    FastCgiCout::write('>');
}
