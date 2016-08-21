#ifndef HTMLSELECTOPTION_H
#define HTMLSELECTOPTION_H

#include "htmlrenderable.h"
#include "htmltag.h"
#include "htmltext.h"

class HtmlSelectOption : public HtmlTag
{
    QString display;

public:
    HtmlSelectOption(const QString&value,const QString&display);

    // HtmlTag interface
public:
    virtual void renderChildren() const override;
};

#endif // HTMLSELECTOPTION_H
