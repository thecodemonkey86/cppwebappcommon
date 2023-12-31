#pragma once

#include <QString>
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT MetaTag
{
protected:
  QString name,content;
  QString httpEquiv;
public:
  MetaTag() = default;
  MetaTag(const QString & name,const QString &content);
  const QString & getName() const;
  MetaTag &setName(const QString &value);
  const QString & getContent() const;
  MetaTag&  setContent(const QString &value);

  QString toHtmlString() const;
  const QString &getHttpEquiv() const;
  MetaTag &setHttpEquiv(const QString &newHttpEquiv);
};

