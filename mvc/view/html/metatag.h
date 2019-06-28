#ifndef METATAG_H
#define METATAG_H
#include <QString>
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT MetaTag
{
protected:
  QString name,content;
public:
  MetaTag() = default;
  MetaTag(const QString & name,const QString &content);
  const QString & getName() const;
  void setName(const QString &value);
  const QString & getContent() const;
  void setContent(const QString &value);

  QString toHtmlString() const;
};

#endif // METATAG_H
