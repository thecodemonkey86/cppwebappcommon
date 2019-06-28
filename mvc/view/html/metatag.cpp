#include "metatag.h"

MetaTag::MetaTag(const QString &name, const QString &content)
{
  this->name = name;
  this->content = content;
}

const QString &  MetaTag::getName() const
{
  return name;
}

void MetaTag::setName(const QString &value)
{
  name = value;
}

const QString &  MetaTag::getContent() const
{
  return content;
}

void MetaTag::setContent(const QString &value)
{
  content = value;
}

QString MetaTag::toHtmlString() const
{
  return QStringLiteral("<meta name=\"%1\" content=\"%2\"/>").arg(name.toHtmlEscaped(),content.toHtmlEscaped());
}

