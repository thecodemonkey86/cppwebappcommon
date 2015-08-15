#ifndef SESSIONVALUE_H
#define SESSIONVALUE_H
#include "basebean.h"
#include <QString>
#include <QVariant>
#include <QDate>
#include "nullable.h"
#include "beanquery.h"
#include "session.h"
class Session;
class SessionValue: public BaseBean{
public: static const char* TABLENAME;
protected: QString _previousSessionId;
protected: QString sessionId;
protected: QString _previousKey;
protected: QString key;
protected: Nullable<QByteArray> value;
protected: QByteArray md5Hash;
protected: bool loaded;
protected: bool valueModified;
protected: bool md5HashModified;
protected: Session* session;
public: SessionValue () ;
public: QString getTableName () ;
public: QString getSessionId () const ;
public: QString getKey () const ;
public: Nullable<QByteArray> getValue () ;
public: QByteArray getMd5Hash () ;
public: Session* getSession () ;
public: SessionValue* setValue (const QByteArray& value) ;
protected: SessionValue* setValueInternal (const Nullable<QByteArray>& value) ;
public: SessionValue* setValueNull () ;
public: SessionValue* setMd5Hash (const QByteArray& md5Hash) ;
protected: SessionValue* setMd5HashInternal (const QByteArray& md5Hash) ;
public: SessionValue* setSessionId (const QString& sessionId) ;
protected: SessionValue* setSessionIdInternal (const QString& sessionId) ;
public: SessionValue* setKey (const QString& key) ;
protected: SessionValue* setKeyInternal (const QString& key) ;
protected: QString getInsertFields () ;
protected: QString getInsertValuePlaceholders () ;
protected: QList<QVariant>* getInsertParams () ;
protected: QString getUpdateFields (QList<QVariant>* params) ;
protected: QString getUpdateCondition () ;
protected: QList<QVariant>* getUpdateConditionParams () ;
public: static SessionValue* getById (QString sessionId,QString key) ;
public: static QString getSelectFields (const QString& alias) ;
public: static SessionValue* getByRecord (const QSqlRecord& record,const QString& alias) ;
public: static BeanQuery<SessionValue>* createQuery () ;
public: static QString getAllSelectFields (QString artistTableAlias) ;
public: static void addRelatedTableJoins (BeanQuery<SessionValue>* query) ;
public: static QList<SessionValue*>* fetchList (QSqlQuery* res) ;
public: static SessionValue* fetchOne (QSqlQuery* res) ;
public: void load () ;
public: bool remove () ;
public: static SessionValue* createNew () ;
public: bool exists (QString sessionId,QString key) ;
bool operator < (const SessionValue& other) const {
return sessionId < other.sessionId&&key < other.key;
}
bool operator == (const SessionValue& other) const {
return sessionId == other.sessionId&&key == other.key;
}
};
inline uint qHash (const SessionValue& other) {
return ::qHash(other.getSessionId())+::qHash(other.getKey());
}
#endif