#ifndef REQUESTPARAM_H
#define REQUESTPARAM_H

#include "abstractrequestparam.h"

template <class T>
class RequestParam : public AbstractRequestParam
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

    T getValue() const {
        return value;
    }
    virtual QString toString(){
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
