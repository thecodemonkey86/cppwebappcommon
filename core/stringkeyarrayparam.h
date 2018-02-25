#ifndef STRINGKEYARRAYPARAM_H
#define STRINGKEYARRAYPARAM_H
#include <QHash>
#include "abstractstringkeyarrayparam.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT StringKeyArrayParam
        : public QHash<QString,AbstractStringKeyArrayParam*>,
        public AbstractStringKeyArrayParam
{
protected:
    QString name;
public:
    StringKeyArrayParam(const QString &name);
    virtual ~StringKeyArrayParam();
    virtual QString toString();
    QString getArrayValue(int dimensionsCount, ...);
    QString getArrayValue(const QStringList & arrayKeys);
    virtual AbstractStringKeyArrayParam* val(const QString&key);
    void incrementDimension();
};

#endif // STRINGKEYARRAYPARAM_H
