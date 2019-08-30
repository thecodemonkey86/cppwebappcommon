#ifndef STRINGKEYSUBARRAYPARAM_H
#define STRINGKEYSUBARRAYPARAM_H

#include <core/abstractstringkeyarrayparam.h>
#include <QStringList>



class StringKeySubArrayParam : public QStringList, public AbstractStringKeyArrayParam
{
public:
  StringKeySubArrayParam();

  // AbstractRequestParam interface
public:
  QString toString() const override;

  // AbstractStringKeyArrayParam interface
public:
  AbstractStringKeyArrayParam *val(const QString &key) const override;
};





#endif // STRINGKEYSUBARRAYPARAM_H
