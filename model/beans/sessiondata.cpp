#include "sessiondata.h"
#include "basebean.h"
#include <QString>
#include <QVariant>
#include <QDate>
#include "nullable.h"
#include "beanquery.h"
#include "session.h"
SessionData::SessionData () {
loaded = false;
session = NULL;
}
QString SessionData::getTableName () {
return QString(TABLENAME);
}
QString SessionData::getSessionId () const {
return sessionId;
}
QString SessionData::getKey () const {
return key;
}
Nullable<QByteArray> SessionData::getValue () {
return value;
}
Session* SessionData::getSession () {
if (!loaded){
load();
}

return session;
}
SessionData* SessionData::setValue (const QByteArray& value) {
this->valueModified=true;
this->value=Nullable<QByteArray>(value);
return this;
}
SessionData* SessionData::setValueInternal (const Nullable<QByteArray>& value) {
this->value=value;
return this;
}
SessionData* SessionData::setValueNull () {
this->valueModified = true;
this->value.setNull();
return this;
}
SessionData* SessionData::setSessionId (const QString& sessionId) {
if (!insert){
this->idModified = true;
this->_previousSessionId = this->sessionId;
}

this->sessionId=sessionId;
return this;
}
SessionData* SessionData::setSessionIdInternal (const QString& sessionId) {
this->sessionId=sessionId;
return this;
}
SessionData* SessionData::setKey (const QString& key) {
if (!insert){
this->idModified = true;
this->_previousKey = this->key;
}

this->key=key;
return this;
}
SessionData* SessionData::setKeyInternal (const QString& key) {
this->key=key;
return this;
}
QString SessionData::getInsertFields () {
return QString("session_id,key,value");
}
QString SessionData::getInsertValuePlaceholders () {
return QString("?,?,?");
}
QList<QVariant>* SessionData::getInsertParams () {
QList<QVariant>* params=new QList<QVariant>();
params->append(sessionId);
params->append(key);
params->append(value.isNull()? QVariant() : value.val());
return params;
}
QString SessionData::getUpdateFields (QList<QVariant>* params) {
QString query;
if (idModified){
params->append(sessionId);
query += QString(",session_id=?");
params->append(key);
query += QString(",key=?");
}

if (valueModified){
params->append(value.isNull()? QVariant() : value.val());
query += QString(",value=?");
}

return query.mid(1);
}
QString SessionData::getUpdateCondition () {
return QString("session_id=? AND key=?");
}
QList<QVariant>* SessionData::getUpdateConditionParams () {
QList<QVariant>* params=new QList<QVariant>();
if (!idModified){
params->append(sessionId);
params->append(key);
} else {
params->append(_previousSessionId);
params->append(_previousKey);
}

return params;
}
SessionData* SessionData::getById (QString sessionId,QString key) {
SqlQuery*q = sqlCon->buildQuery();
QSqlQuery* res= q->select(SessionData::getSelectFields(QString("b1"))+QChar(',')+Session::getSelectFields(QString("b2")))->from(QString(SessionData::TABLENAME),QString("b1"))->leftJoin(Session::TABLENAME,QString("b2"),QString("b1.session_id = b2.id"))->where(QString("b1.session_id=?"),sessionId)->where(QString("b1.key=?"),key)->execQuery();
if (res->next()){
SessionData* b1 = SessionData::getByRecord(res->record(),QString("b1"));
b1->loaded = true;
do {
Session* b2 = Session::getByRecord(res->record(),QString("b2"));
if (b1->session == NULL){
b1->session = b2;
}

} while(res->next());
delete res;
delete q;
return b1;
}

delete res;
delete q;
throw new SqlException(sqlCon);
}
QString SessionData::getSelectFields (const QString& alias) {
if (alias.isEmpty()){
return QString("session_id as session_data__session_id,key as session_data__key,value as session_data__value") ;
} else {
return alias + QString(".session_id as ") + alias + QString("__session_id")+QChar(',')+alias + QString(".key as ") + alias + QString("__key")+QChar(',')+alias + QString(".value as ") + alias + QString("__value") ;
}

}
SessionData* SessionData::getByRecord (const QSqlRecord& record,const QString& alias) {
SessionData* bean = new SessionData ();
return bean->setValueInternal(record.value(alias + QString("__value")).toByteArray())->setSessionIdInternal(record.value(alias + QString("__session_id")).toString())->setKeyInternal(record.value(alias + QString("__key")).toString());
}
BeanQuery<SessionData>* SessionData::createQuery () {
return new BeanQuery<SessionData> (sqlCon->buildQuery()) ;
}
QString SessionData::getAllSelectFields (QString artistTableAlias) {
return SessionData::getSelectFields(QString(artistTableAlias))+QChar(',')+Session::getSelectFields(QString("b2"));
}
void SessionData::addRelatedTableJoins (BeanQuery<SessionData>* query) {
query->leftJoin(Session::TABLENAME,QString("b2"),QString("b1.session_id = b2.id"));
}
QList<SessionData*>* SessionData::fetchList (QSqlQuery* res) {
QList<SessionData*>* beans = new QList<SessionData*>();
SessionData* b1 = NULL;
while (res->next()){
b1 = SessionData::getByRecord(res->record(),QString("b1"));
b1->loaded = true;
beans->append(b1);
if (!res->record().value(QString("b2__session_id")).isNull()){
Session* b2 = Session::getByRecord(res->record(),QString("b2"));
b1->session = b2;
}

}
return beans;
}
SessionData* SessionData::fetchOne (QSqlQuery* res) {
SessionData* b1 = NULL;
if (res->next()){
b1 = SessionData::getByRecord(res->record(),QString("b1"));
if (!res->record().value(QString("b2__session_id")).isNull()){
Session* b2 = Session::getByRecord(res->record(),QString("b2"));
b1->session = b2;
}

}

return b1;
}
void SessionData::load () {
loaded = true;
SqlQuery* q = sqlCon->buildQuery();
QSqlQuery* res = q->select(Session::getSelectFields(QString("b2")))->from(SessionData::TABLENAME ,QString("b1"))->leftJoin(Session::TABLENAME,QString("b2"),QString("b1.session_id = b2.id"))->where(QString("b1.session_id = ?"),getSessionId())->where(QString("b1.key = ?"),getKey())->execQuery();
if (res->next()){
do {
Session* b2 = Session::getByRecord(res->record(),QString("b2"));
if (this->session == NULL){
this->session = b2;
}

} while(res->next());
}

}
bool SessionData::remove () {
SqlQuery* q = sqlCon->buildQuery()->deleteFrom(QString(SessionData::TABLENAME))->where(QString("session_id = ?"),getSessionId())->where(QString("key = ?"),getKey());
return q->execute();
}
void SessionData::setLoaded () {
this->loaded = true;
}
const char* SessionData::TABLENAME = "session_data" ;
