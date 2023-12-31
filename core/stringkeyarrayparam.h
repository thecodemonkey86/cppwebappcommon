#pragma once

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
    virtual QString  toString() const override;
    virtual const AbstractStringKeyArrayParam* val(const QString&key) const override;
    void incrementDimension() ;
};

