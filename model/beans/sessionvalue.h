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
protected: QByteArray _previousMd5Hash;
protected: QByteArray md5Hash;
protected: QString _previousKey;
protected: QString key;
protected: Nullable<QByteArray> value;
protected: bool loaded;
protected: bool valueModified;
protected: Session* session;
public: SessionValue () ;
public: QString getTableName () ;
public: QString getSessionId () const ;
public: QByteArray getMd5Hash () const ;
public: QString getKey () const ;
public: Nullable<QByteArray> getValue () ;
public: Session* getSession () ;
public: SessionValue* setValue (const QByteArray& value) ;
protected: SessionValue* setValueInternal (const Nullable<QByteArray>& value) ;
public: SessionValue* setValueNull () ;
public: SessionValue* setSessionId (const QString& sessionId) ;
protected: SessionValue* setSessionIdInternal (const QString& sessionId) ;
public: SessionValue* setMd5Hash (const QByteArray& md5Hash) ;
protected: SessionValue* setMd5HashInternal (const QByteArray& md5Hash) ;
public: SessionValue* setKey (const QString& key) ;
protected: SessionValue* setKeyInternal (const QString& key) ;
protected: QString getInsertFields () ;
protected: QString getInsertValuePlaceholders () ;
protected: QList<QVariant>* getInsertParams () ;
protected: QString getUpdateFields (QList<QVariant>* params) ;
protected: QString getUpdateCondition () ;
protected: QList<QVariant>* getUpdateConditionParams () ;
public: static SessionValue* getById (QString sessionId,QByteArray md5Hash,QString key) ;
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
public: bool exists (QString sessionId,QByteArray md5Hash,QString key) ;
bool operator < (const SessionValue& other) const {
return sessionId < other.sessionId&&md5Hash < other.md5Hash&&key < other.key;
}
bool operator == (const SessionValue& other) const {
return sessionId == other.sessionId&&md5Hash == other.md5Hash&&key == other.key;
}
};
inline uint qHash (const SessionValue& other) {
return ::qHash(other.getSessionId())+::qHash(other.getMd5Hash())+::qHash(other.getKey());
}
#endif