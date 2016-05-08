#ifndef FORM_H
#define FORM_H

#include <QString>
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "model/sessiondata.h"
#include <QDate>

class Form
{
protected:
    RequestData* request;
    ServerData * serverData;
    SessionData * sessionData;

    QString submitFieldName;
    virtual bool isSubmitted()=0;
public:
    Form(const QString&submitFieldName);
    virtual ~Form();
    virtual QString stringValue(const QString&name)=0;
    virtual int intValue(const QString&name)=0;
    virtual QDate dateValue(const QString&name)=0;
    virtual double doubleValue(const QString&name)=0;
    virtual bool isValueEmpty(const QString&name);
    void setRequestData(RequestData *value);
    void setSessionData(SessionData *value);
    void setServerData(ServerData *value);
};

#endif // FORM_H
