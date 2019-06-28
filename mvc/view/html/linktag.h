#ifndef LINKTAG_H
#define LINKTAG_H

#include <QString>
#include "webappcommon_global.h"


class WEBAPPCOMMONSHARED_EXPORT LinkTag
{
  QString href, type, rel;
public:
  LinkTag() = default;
  QString getHref() const;
  LinkTag & setHref(const QString &value);
  QString getType() const;
   LinkTag & setType(const QString &value);
  QString getRel() const;
  LinkTag & setRel(const QString &value);
  QString toHtmlString() const;
};

#endif // LINKTAG_H
