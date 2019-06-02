#ifndef REQUESTPARAM_H
#define REQUESTPARAM_H

#include "abstractrequestparam.h"
#include "webappcommon_global.h"
#include <QUrl>

class WEBAPPCOMMONSHARED_EXPORT RequestParam : public AbstractRequestParam
{
protected:
    QString name;
    QString value;
public:
    RequestParam(const QString &name,const QString& value);
    RequestParam(const RequestParam& other) = default;
    virtual ~RequestParam() = default;

    const QString & getValue() const;
    virtual const QString &  toString() const;

    const QString & getName() const;
    void setName(const QString &name);
};



#endif // REQUESTPARAM_H
