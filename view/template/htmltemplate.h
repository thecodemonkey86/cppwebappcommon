#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

#include "abstracttemplate.h"
#include <QSet>
#include <memory>

using namespace std;

class WEBAPPCOMMONSHARED_EXPORT HtmlTemplate : public AbstractTemplate
{
public:
    HtmlTemplate();
    ~HtmlTemplate();
    virtual void update(const MvcMessage& updateMsg);
    void outAttr(const QString &attr, const QString &value);
     void outBeginTag(const QString &tag);
     void outEndTag(const QString &tag);
//     shared_ptr<AbstractTemplate> getBodyTemplate() const;
     void setBodyTemplate(unique_ptr<AbstractTemplate> bodyTemplate);

protected:
     void renderHeader();
     void renderFooter();

     unique_ptr<AbstractTemplate> bodyTemplate;
     QSet<QString> includeCss;
     QSet<QString> includeJs;
};

#endif // HTMLTEMPLATE_H
