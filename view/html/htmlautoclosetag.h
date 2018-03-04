#ifndef HTMLTAG_H
#define HTMLTAG_H

#include <QString>
#include "fastcgicout.h"
#include <QHash>
#include "htmlrenderable.h"
#include "webappcommon_global.h"
#include <QVector>

class WEBAPPCOMMONSHARED_EXPORT HtmlAutoCloseTag : public HtmlRenderable
{
protected:
    QString tag;
    QVector<QPair<QString,QString>> attributes;
public:
    HtmlAutoCloseTag(const QString &tag);
    void setAttribute(const QString&name, const  QString&value);
    virtual void render() const;
};

#endif // HTMLTAG_H
