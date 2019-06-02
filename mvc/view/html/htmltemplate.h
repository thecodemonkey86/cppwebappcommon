#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

#include "../abstractview.h"
#include <QSet>
#include <memory>
#include "core/httpheader.h"
#include "core/fastcgioutput.h"
#include "util/collection/orderedset.h"
using namespace QtCommon2;
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT HtmlTemplate : public AbstractView
{
public:
    inline void outAttr(const QString &attr, const QString &value) const;
    inline void outBeginTag(const QString &tag) const;
    inline void outBeginTagWithAttrs(const QString &tag) const;
    inline void outEndTag(const QString &tag) const;
   // virtual void beforeRender();
protected:

     void renderHeader() const;
     void renderFooter() const;
     virtual void renderInlineJs() const;
     virtual void renderInlineCss() const;

     OrderedSet<QString> includeCss;
     OrderedSet<QString> includeJs;
     // AbstractTemplate interface
public:
     virtual QString getHttpContentType() const;
     void addCssFiles(const QStringList&cssFiles);
     void addJsFiles(const QStringList&jssFiles);
     void addCssFile(const QString&cssFile);
     void addJsFile(const QString&jssFile);
//     virtual QString getBaseUrl() const;
//     void setBaseUrl(const QString &value);
};

#endif // HTMLTEMPLATE_H
