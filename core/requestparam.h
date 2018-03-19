#ifndef REQUESTPARAM_H
#define REQUESTPARAM_H

#include "abstractrequestparam.h"
#include "webappcommon_global.h"
template <class T>
class WEBAPPCOMMONSHARED_EXPORT RequestParam : public AbstractRequestParam
{
protected:
    QString name;
    T value;
public:
    RequestParam(const QString &name,const T& value) : AbstractRequestParam() {
        this->name = name;
        this->value = value;
    }



    virtual ~RequestParam() {

    }

    const T & getValue() const {
        return value;
    }
    virtual QString toString() const{
        return name;
    }

    QString getName() const {
        return name;
    }
    void setName(const QString &name) {
        this->name = name;
    }
};



#endif // REQUESTPARAM_H
