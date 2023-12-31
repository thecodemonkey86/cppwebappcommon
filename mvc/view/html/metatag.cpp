#include "metatag.h"

const QString &MetaTag::getHttpEquiv() const
{
  return httpEquiv;
}

MetaTag& MetaTag::setHttpEquiv(const QString &newHttpEquiv)
{
  httpEquiv = newHttpEquiv;
  return *this;
}

const QString &  MetaTag::getName() const
{
  return name;
}

MetaTag&  MetaTag::setName(const QString &value)
{
  name = value;
  return *this;
}

const QString &  MetaTag::getContent() const
{
  return content;
}

MetaTag&  MetaTag::setContent(const QString &value)
{
  content = value;
  return *this;
}

QString MetaTag::toHtmlString() const
{
  QString html=QStringLiteral("<meta");
  if(!name.isNull())
  {
    html+=QStringLiteral(" name=\"%1\"").arg(name);
  }
  if(!httpEquiv.isNull())
  {
    html+=QStringLiteral(" http-equiv=\"%1\"").arg(httpEquiv);
  }
   html+=QStringLiteral(" content=\"%1\"").arg(content);
  return html+"/>";
}

