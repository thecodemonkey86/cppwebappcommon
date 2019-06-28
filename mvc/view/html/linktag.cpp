#include "linktag.h"

QString LinkTag::getHref() const
{
  return href;
}

 LinkTag & LinkTag::setHref(const QString &value)
{
  href = value;
  return *this;
}

QString LinkTag::getType() const
{
  return type;
}

 LinkTag & LinkTag::setType(const QString &value)
{
  type = value;
  return *this;
}

QString LinkTag::getRel() const
{
  return rel;
}

 LinkTag & LinkTag::setRel(const QString &value)
{
  rel = value;
  return *this;
}

QString LinkTag::toHtmlString() const
{
  QString  html("<link href=\"%1\"");
  if(!rel.isEmpty()){
    html += QStringLiteral(" rel=\"%1\"").arg(rel);
  }
  if(!type.isEmpty()){
    html += QStringLiteral(" type=\"%1\"").arg(type);
  }
  html+="/>";
  return html.arg(href);
}

