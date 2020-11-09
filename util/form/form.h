#ifndef FORM_H
#define FORM_H

#include <QString>
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/sessiondata.h"
#include <QDate>
#include <QSet>
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
    virtual const QString & stringValue(const QString&name) const=0;
    virtual int intValue(const QString&name) const=0;
    virtual int64_t int64Value(const QString&name) const=0;
    virtual uint32_t uintValue(const QString&name) const=0;
    virtual bool boolValue(const QString&name) const=0;
    virtual QDate dateValue(const QString&name, const QString &format="yyyy-MM-dd") const=0;
    virtual QDateTime dateTimeValue(const QString&name,const QString & format="yyyy-MM-ddThh:mm") const=0;
    virtual double doubleValue(const QString&name) const=0;
    virtual bool isValueEmpty(const QString&name) const=0;
   virtual QVector<int> intArrayValue(const QString&name) const=0;
    virtual QVector<int64_t> int64ArrayValue(const QString&name) const=0;
    virtual QSet<int64_t> int64HashSetValue(const QString &name) const=0;
   virtual ArrayRequestParam * array(const QString&name) const=0;
   virtual QStringList stringArrayValue(const QString&name) const=0;

    int intValue(const QString&name,int defaultValue) const;
    const QString & stringValue(const QString&name, const QString & defaultValue) const;

    int64_t int64Value(const QString&name,int64_t defaultValue) const;
    uint uintValue(const QString&name,uint defaultValue) const;
    bool boolValue(const QString&name,bool defaultValue) const;
    QDate dateValue(const QString&name, const QDate & defaultValue, const QString &format="yyyy-MM-dd") const;
    QDateTime dateTimeValue(const QString&name, const QDateTime & defaultValue,const QString & format="yyyy-MM-ddThh:mm") const;
    double doubleValue(const QString&name,double defaultValue) const;


    virtual bool isSubmitted() const=0;
    virtual bool isSet(const QString & name)const =0;
    virtual bool isSetAndNotEmpty(const QString & name) const;
    virtual bool isNotSetOrEmpty(const QString & name) const;
    virtual StringKeyArrayParam* stringKeyArray(const QString&name) const=0;
    virtual QList<QString> arrayKeys(const QString&name) const=0;
    virtual  const QString & arrayStringValue(const QString&fieldName,const QString&arrayKey) const =0;
    virtual  AbstractStringKeyArrayParam*  arrayValue(const QString&fieldName,const QString&arrayKey) const =0;
    void setSessionData(SessionData *value);
    void setServerData(ServerData *value);
    QString getSubmitFieldName() const;

    template<class E> E enumValue(const QString &name, E defaultValue)
    {
      return isSet(name) ? static_cast<E>(intValue(name)) : defaultValue;
    }
    template<class E> E enumValue(const QString &name)
    {
      return static_cast<E>(intValue(name)) ;
    }
    template<class E> QVector<E> enumArrayValue(const QString&name) const
    {
      QVector<E> result;
      QVector<int> arr = intArrayValue(name);
      for(int a : arr) {
        result += static_cast<E>(a);
      }
      return result;
    }


};

#endif // FORM_H
