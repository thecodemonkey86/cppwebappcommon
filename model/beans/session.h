#ifndef SESSION_H
#define SESSION_H
#include "basebean.h"
#include <QString>
#include <QVariant>
#include <QDate>
#include "nullable.h"
#include "beanquery.h"
class Session: public BaseBean{
public: static const char* TABLENAME;
protected: QVariant _previousId;
protected: QVariant id;
protected: QVariant expirationDate;
protected: bool loaded;
protected: bool expirationDateModified;
public: Session () ;
public: QString getTableName () ;
public: QVariant getId () const ;
public: QVariant getExpirationDate () ;
public: Session* setExpirationDate (const QVariant& expirationDate) ;
protected: Session* setExpirationDateInternal (const QVariant& expirationDate) ;
public: Session* setId (const QVariant& id) ;
protected: Session* setIdInternal (const QVariant& id) ;
protected: QString getInsertFields () ;
protected: QString getInsertValuePlaceholders () ;
protected: QList<QVariant>* getInsertParams () ;
protected: QString getUpdateFields (QList<QVariant>* params) ;
protected: QString getUpdateCondition () ;
protected: QList<QVariant>* getUpdateConditionParams () ;
public: static Session* getById (QVariant id) ;
public: static QString getSelectFields (const QString& alias) ;
public: static Session* getByRecord (const QSqlRecord& record,const QString& alias) ;
public: static BeanQuery<Session>* createQuery () ;
public: static QString getAllSelectFields (QString artistTableAlias) ;
public: static void addRelatedTableJoins (BeanQuery<Session>* query) ;
public: static QList<Session*>* evaluateQuery (QSqlQuery* res) ;
public: void load () ;
public: bool remove () ;
public: void setLoaded () ;
bool operator < (const Session& other) const {
return id < other.id;
}
bool operator == (const Session& other) const {
return id == other.id;
}
};
inline uint qHash (const Session& other) {
return ::qHash(other.getId());
}
#endif
