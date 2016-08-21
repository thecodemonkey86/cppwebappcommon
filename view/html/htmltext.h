#ifndef HTMLTEXT_H
#define HTMLTEXT_H

#include "htmlrenderable.h"
#include "fastcgicout.h"

class HtmlText : public HtmlRenderable
{
protected: QString content;

public:
    HtmlText(const QString &content);

    // HtmlRenderable interface
public:
    virtual void render() const override;
};

#endif // HTMLTEXT_H
