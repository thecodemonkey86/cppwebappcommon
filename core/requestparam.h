#ifndef REQUESTPARAM_H
#define REQUESTPARAM_H

#include "abstractrequestparam.h"
#include "webappcommon_global.h"
#include <QUrl>
class RequestParam;

typedef RequestParam GetParam  ;

class WEBAPPCOMMONSHARED_EXPORT RequestParam : public AbstractRequestParam
{
protected:
    QString name;
    QString value;
public:
    RequestParam(const QString &name,const QString& value);
    RequestParam(const QString &name,int value);
    RequestParam(const RequestParam& other) = default;
    virtual ~RequestParam() override = default;

    const QString & getValue() const;
    QString getPercentEscapedValue() const;
    virtual const QString &  toString() const override ;

    const QString & getName() const;
    void setName(const QString &name);
};



#endif // REQUESTPARAM_H
