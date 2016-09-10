#ifndef HTMLSELECT_H
#define HTMLSELECT_H
#include "htmltag.h"
#include "htmlselectoption.h"
#include "exception/qtexception.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT HtmlSelect : public HtmlTag
{
protected:
    vector<HtmlSelectOption> selectOptions;
public:
    HtmlSelect();
HtmlSelect & option(const  QString&value, const QString&display);
HtmlSelect & options(const vector<QPair<QString,QString>>& options);
HtmlSelect & options(const QVector<HtmlSelectOption>& options);
HtmlSelect & options(const QStringList & values,const QStringList & display );
HtmlSelect & options(const QHash<QString,QString>& options );
HtmlSelect & options(const QMap<QString,QString>& options );

// HtmlTag interface
public:
virtual void renderChildren() const override;
};

#endif // HTMLSELECT_H
