#pragma once

#include "requestparam.h"
#include "abstractrequestparam.h"
#include <QStringList>
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT ArrayRequestParam : public QStringList, public AbstractRequestParam
{
protected:
    QString name;
public:
    ArrayRequestParam(const QString & name);
    virtual ~ArrayRequestParam();
    virtual QString toString() const;
};

