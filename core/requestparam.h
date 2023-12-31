#pragma once


#include "abstractrequestparam.h"
#include "webappcommon_global.h"
class RequestParam;

typedef RequestParam GetParam  ;

class WEBAPPCOMMONSHARED_EXPORT RequestParam : public AbstractRequestParam
{
protected:
    QString name;
    QString value;
public:
    RequestParam(const QString &name,const QString& value);
    RequestParam(const QString &name,uint value);
    RequestParam(const QString &name,int value);
    RequestParam(const QString &name,int64_t value);
    RequestParam(const RequestParam& other) = default;
    virtual ~RequestParam() override = default;

    const QString & getValue() const;
    QString getPercentEscapedValue() const;
    virtual QString  toString() const override ;

    const QString & getName() const;
    void setName(const QString &name);
};



