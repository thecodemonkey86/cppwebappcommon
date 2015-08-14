#ifndef ARRAYREQUESTPARAM_H
#define ARRAYREQUESTPARAM_H
#include "requestparam.h"
#include "abstractrequestparam.h"
#include <QStringList>

class ArrayRequestParam : public QStringList, public AbstractRequestParam
{
protected:
    QString name;
public:
    ArrayRequestParam(const QString & name);
    virtual ~ArrayRequestParam();
    virtual QString toString();
};

#endif // ARRAYREQUESTPARAM_H
