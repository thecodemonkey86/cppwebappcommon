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
   virtual QVector<int> intArrayValue(const QString&name) const=0;
   virtual ArrayRequestParam * array(const QString&name) const=0;
    virtual QString stringValue(const QString&name, const QString & defaultValue) const;
    virtual int intValue(const QString&name,int defaultValue) const;
    virtual bool boolValue(const QString&name,bool defaultValue) const;
    virtual QDate dateValue(const QString&name, const QDate & defaultValue) const;
    virtual QDateTime dateTimeValue(const QString&name, const QDateTime & defaultValue) const;
    virtual double doubleValue(const QString&name,double defaultValue) const;

    virtual bool isSubmitted() const=0;
    virtual bool isSet(const QString & name)const =0;
    virtual bool isSetAndNotEmpty(const QString & name) const;
    void setSessionData(SessionData *value);
    void setServerData(ServerData *value);
};

#endif // FORM_H
