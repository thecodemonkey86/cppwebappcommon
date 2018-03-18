#ifndef HTMLTAG_H
#define HTMLTAG_H

#include <QString>
#include <QHash>
#include "htmlrenderable.h"
#include "webappcommon_global.h"
#include <QVector>
#include <memory>
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT HtmlTag : public HtmlRenderable
{
protected:
    QString tag;
    QVector<QString> classes;
    QVector<QPair<QString,QString>> attributes;
   // std::vector<shared_ptr<HtmlRenderable>> children;
public:
    HtmlTag(const QString &tag);
    void setAttribute(const QString&name, const  QString&value);
    void addClass(const QString & cls);
    virtual void render() const;
    virtual void renderChildren() const =0;
};

#endif // HTMLTAG_H
