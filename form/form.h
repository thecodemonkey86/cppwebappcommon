#ifndef FORM_H
#define FORM_H

#include <QString>
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/sessiondata.h"
#include <QDate>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT Form
{
protected:
    RequestData* request;
    ServerData * serverData;
    SessionData * sessionData;

    QString submitFieldName;

public:
    Form(RequestData *request,const QString&submitFieldName);
    virtual ~Form();
    virtual QString stringValue(const QString&name) const=0;
    virtual int intValue(const QString&name) const=0;
    virtual bool boolValue(const QString&name) const=0;
    virtual QDate dateValue(const QString&name) const=0;
    virtual QDateTime dateTimeValue(const QString&name) const=0;
    virtual double doubleValue(const QString&name) const=0;
    virtual bool isValueEmpty(const QString&name) const=0;
    virtual bool isSubmitted() const=0;
    virtual bool isSet(const QString & name)=0;
    virtual bool isSetAndNotEmpty(const QString & name);
    void setSessionData(SessionData *value);
    void setServerData(ServerData *value);
};

#endif // FORM_H
