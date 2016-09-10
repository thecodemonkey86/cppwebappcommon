#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

#include "../abstractview.h"
#include <QSet>
#include <memory>
#include "core/httpheader.h"
#include  "fastcgicout.h"
#include "util/orderedset.h"

using namespace std;

class WEBAPPCOMMONSHARED_EXPORT HtmlTemplate : public AbstractView
{
public:
    virtual void update(unique_ptr<MvcMessage>) override;

    void outAttr(const QString &attr, const QString &value);
    inline void outBeginTag(const QString &tag);
    inline void outBeginTagWithAttrs(const QString &tag);
    inline void outEndTag(const QString &tag);
   // virtual void beforeRender();
protected:
     protected: static FastCgiCout output;

     virtual void render();
     virtual void renderBody()=0;
     void renderHeader();
     void renderFooter();
     virtual void renderInlineJs();
     virtual void renderInlineCss();

     OrderedSet<QString> includeCss;
     OrderedSet<QString> includeJs;
    QString baseUrl;
     // AbstractTemplate interface
public:
     virtual QString getHttpContentType();
     void addCssFiles(const QStringList&cssFiles);
     void addJsFiles(const QStringList&jssFiles);
     QString getBaseUrl() const;
     void setBaseUrl(const QString &value);
};

#endif // HTMLTEMPLATE_H
