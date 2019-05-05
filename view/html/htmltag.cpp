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
    output('<');
    output(tag);
    output(' ');
    for(const QPair<QString,QString> & attr : this->attributes) {
        output(attr.first);
        output("=\"");
        output(attr.second.toHtmlEscaped());
        output("\" ");
    }


    if (classes.size()>0) {
        output(" class=\"");
        for(int i=0;i<classes.size()-1;i++) {
            output(classes[i].toHtmlEscaped());
            output(' ');
        }
        output(classes.last().toHtmlEscaped());
        output('"');
    }

    output('>');

    renderChildren();

    output("</");
    output(tag);
    output('>');
}
