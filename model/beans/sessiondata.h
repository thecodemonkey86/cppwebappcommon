#ifndef SESSIONDATA_H
#define SESSIONDATA_H
#include "basebean.h"
#include <QString>
#include <QVariant>
#include <QDate>
#include "nullable.h"
#include "beanquery.h"
#include "session.h"
class Session;
class SessionData: public BaseBean{
public: static const char* TABLENAME;
protected: QString _previousSessionId;
protected: QString sessionId;
protected: QString _previousKey;
protected: QString key;
protected: Nullable<QByteArray> value;
protected: bool loaded;
protected: bool valueModified;
protected: Session* session;
public: SessionData () ;
public: QString getTableName () ;
public: QString getSessionId () const ;
public: QString getKey () const ;
public: Nullable<QByteArray> getValue () ;
public: Session* getSession () ;
public: SessionData* setValue (const QByteArray& value) ;
protected: SessionData* setValueInternal (const Nullable<QByteArray>& value) ;
public: SessionData* setValueNull () ;
public: SessionData* setSessionId (const QString& sessionId) ;
protected: SessionData* setSessionIdInternal (const QString& sessionId) ;
public: SessionData* setKey (const QString& key) ;
protected: SessionData* setKeyInternal (const QString& key) ;
protected: QString getInsertFields () ;
protected: QString getInsertValuePlaceholders () ;
protected: QList<QVariant>* getInsertParams () ;
protected: QString getUpdateFields (QList<QVariant>* params) ;
protected: QString getUpdateCondition () ;
protected: QList<QVariant>* getUpdateConditionParams () ;
public: static SessionData* getById (QString sessionId,QString key) ;
public: static QString getSelectFields (const QString& alias) ;
public: static SessionData* getByRecord (const QSqlRecord& record,const QString& alias) ;
public: static BeanQuery<SessionData>* createQuery () ;
public: static QString getAllSelectFields (QString artistTableAlias) ;
public: static void addRelatedTableJoins (BeanQuery<SessionData>* query) ;
public: static QList<SessionData*>* fetchList (QSqlQuery* res) ;
public: static SessionData* fetchOne (QSqlQuery* res) ;
public: void load () ;
public: bool remove () ;
public: void setLoaded () ;
bool operator < (const SessionData& other) const {
return sessionId < other.sessionId&&key < other.key;
}
bool operator == (const SessionData& other) const {
return sessionId == other.sessionId&&key == other.key;
}
};
inline uint qHash (const SessionData& other) {
return ::qHash(other.getSessionId())+::qHash(other.getKey());
}
#endif