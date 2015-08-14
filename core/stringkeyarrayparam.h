#ifndef STRINGKEYARRAYPARAM_H
#define STRINGKEYARRAYPARAM_H
#include <QMap>
#include "abstractstringkeyarrayparam.h"

class StringKeyArrayParam : public QMap<QString,AbstractStringKeyArrayParam*>, public AbstractStringKeyArrayParam
{
protected:
    QString name;
public:
    StringKeyArrayParam(const QString &name);
    virtual ~StringKeyArrayParam();
    virtual QString toString();
    QString getArrayValue(int dimensionsCount, ...);
    virtual AbstractStringKeyArrayParam* val(const QString&key);
    void incrementDimension();
};

#endif // STRINGKEYARRAYPARAM_H
