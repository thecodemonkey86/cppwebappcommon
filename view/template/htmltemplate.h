#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

#include "abstracttemplate.h"
#include <QSet>

class WEBAPPCOMMONSHARED_EXPORT HtmlTemplate : public AbstractTemplate
{
public:
    HtmlTemplate();
    ~HtmlTemplate();
    virtual void update(MvcMessage* updateMsg);
    virtual void render();
    void outAttr(const QString &attr, const QString &value);
     void outBeginTag(const QString &tag);
     void outEndTag(const QString &tag);
     AbstractTemplate *getBodyTemplate() const;
     void setBodyTemplate(AbstractTemplate *value);

protected:
     void renderHeader();
     void renderFooter();

     AbstractTemplate* bodyTemplate;
     QSet<QString> includeCss;
     QSet<QString> includeJs;
};

#endif // HTMLTEMPLATE_H
