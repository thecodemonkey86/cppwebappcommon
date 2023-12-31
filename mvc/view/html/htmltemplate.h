#pragma once


#include "../abstractview.h"
#include <QSet>
#include <memory>
#include "core/httpheader.h"
#include "core/fastcgioutput.h"
#include "util/collection/orderedset.h"
#include "linktag.h"
#include "metatag.h"

using namespace QtCommon2;


class WEBAPPCOMMONSHARED_EXPORT HtmlTemplate : public AbstractView
{
public:
    void outAttr(const QString &attr, const QString &value) const;
    void outBeginTag(const QString &tag) const;
    void outBeginTagWithAttrs(const QString &tag) const;
    void outEndTag(const QString &tag) const;
   // virtual void beforeRender();
protected:

     void renderHeader() const;
     void renderFooter() const;
     virtual void renderInlineJs() const;
     virtual void renderInlineCss() const;

     OrderedSet<QString> includeCss;
     OrderedSet<QString> includeJs;
     OrderedSet<QString> includeFonts;
     QList<MetaTag> metaTags;
     QList<LinkTag> linkTags;
     QString title;
     // AbstractTemplate interface
public:
     virtual QString getHttpContentType() const;
     void addCssFiles(const QStringList&cssFiles);
     void addJsFiles(const QStringList&jssFiles);
     void addCssFile(const QString&cssFile);
     void addJsFile(const QString&jssFile);
     void addFont(const QString&font);
     void addMetaTag(const MetaTag&meta);
     void addLinkTag(const LinkTag&link);
//     virtual QString getBaseUrl() const;
//     void setBaseUrl(const QString &value);
     QString getTitle() const;
     void setTitle(const QString &value);
};

