#ifndef SESSION_H
#define SESSION_H
#include "basebean.h"
#include <QString>
#include <QVariant>
#include <QDate>
#include "nullable.h"
#include "beanquery.h"
#include "model/beans/sessionvalue.h"
class SessionValue;
class Session: public BaseBean{
public: static const char* TABLENAME;
protected: QString _previousId;
protected: QString id;
protected: QByteArray md5Hash;
protected: QDateTime expirationDate;
protected: bool loaded;
protected: bool md5HashModified;
protected: bool expirationDateModified;
protected: QSet<SessionValue>* sessionValues;
public: Session () ;
public: ~Session () ;
public: QString getTableName () ;
public: QString getId () const ;
public: QByteArray getMd5Hash () ;
public: QDateTime getExpirationDate () ;
public: QList<SessionValue*>* getSessionValues () ;
public: Session* setMd5Hash (const QByteArray& md5Hash) ;
protected: Session* setMd5HashInternal (const QByteArray& md5Hash) ;
public: Session* setExpirationDate (const QDateTime& expirationDate) ;
protected: Session* setExpirationDateInternal (const QDateTime& expirationDate) ;
public: Session* setId (const QString& id) ;
protected: Session* setIdInternal (const QString& id) ;
protected: QString getInsertFields () ;
protected: QString getInsertValuePlaceholders () ;
protected: QList<QVariant>* getInsertParams () ;
protected: QString getUpdateFields (QList<QVariant>* params) ;
protected: QString getUpdateCondition () ;
protected: QList<QVariant>* getUpdateConditionParams () ;
public: static Session* getById (QString id) ;
public: static QString getSelectFields (const QString& alias) ;
public: static Session* getByRecord (const QSqlRecord& record,const QString& alias) ;
public: static BeanQuery<Session>* createQuery () ;
public: static QString getAllSelectFields (QString artistTableAlias) ;
public: static void addRelatedTableJoins (BeanQuery<Session>* query) ;
public: static QList<Session*>* fetchList (QSqlQuery* res) ;
public: static Session* fetchOne (QSqlQuery* res) ;
public: void load () ;
public: bool remove () ;
public: static Session* createNew () ;
public: bool exists (QString id) ;
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