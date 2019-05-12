#ifndef STRINGKEYARRAYPARAM_H
#define STRINGKEYARRAYPARAM_H
class StringKeyArrayParam;
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
    virtual QString toString() const;
    QString arrayValue(int dimensionsCount, ...) const;
    QString arrayValue(const QStringList & arrayKeys) const;
    virtual AbstractStringKeyArrayParam* val(const QString&key) const;
    StringKeyArrayParam* stringKeyArray(const QString&key) const;
    void incrementDimension() ;
};

#endif // STRINGKEYARRAYPARAM_H
