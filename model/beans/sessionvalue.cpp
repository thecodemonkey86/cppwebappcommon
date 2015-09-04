#include "sessionvalue.h"
#include "basebean.h"
#include <QString>
#include <QVariant>
#include <QDate>
#include "nullable.h"
#include "beanquery.h"
#include "model/beans/session.h"
SessionValue::SessionValue () {
loaded = false;
session = NULL;
autoIncrement = false;
}
SessionValue::~SessionValue () {
}
QString SessionValue::getTableName () {
return QString(TABLENAME);
}
QString SessionValue::getSessionId () const {
return sessionId;
}
QString SessionValue::getKey () const {
return key;
}
Nullable<QByteArray> SessionValue::getValue () {
return value;
}
Session* SessionValue::getSession () {
if (!loaded){
load();
}

return session;
}
SessionValue* SessionValue::setValue (const QByteArray& value) {
this->valueModified=true;
this->value=Nullable<QByteArray>(value);
return this;
}
SessionValue* SessionValue::setValueInternal (const Nullable<QByteArray>& value) {
this->value=value;
return this;
}
SessionValue* SessionValue::setValueNull () {
this->valueModified = true;
this->value.setNull();
return this;
}
SessionValue* SessionValue::setSessionId (const QString& sessionId) {
if (!insert){
this->idModified = true;
this->_previousSessionId = this->sessionId;
}

this->sessionId=sessionId;
return this;
}
SessionValue* SessionValue::setSessionIdInternal (const QString& sessionId) {
this->sessionId=sessionId;
return this;
}
SessionValue* SessionValue::setKey (const QString& key) {
if (!insert){
this->idModified = true;
this->_previousKey = this->key;
}

this->key=key;
return this;
}
SessionValue* SessionValue::setKeyInternal (const QString& key) {
this->key=key;
return this;
}
QString SessionValue::getInsertFields () {
return QString("session_id,key,value");
}
QString SessionValue::getInsertValuePlaceholders () {
return QString("?,?,?");
}
QList<QVariant>* SessionValue::getInsertParams () {
QList<QVariant>* params=new QList<QVariant>();
params->append(sessionId);
params->append(key);
params->append(value.isNull()? QVariant() : value.val());
return params;
}
QString SessionValue::getUpdateFields (QList<QVariant>* params) {
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
QString SessionValue::getUpdateCondition () {
return QString("session_id=? AND key=?");
}
QList<QVariant>* SessionValue::getUpdateConditionParams () {
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
SessionValue* SessionValue::getById (QString sessionId,QString key) {
SqlQuery*q = sqlCon->buildQuery();
QSqlQuery* res= q->select(SessionValue::getSelectFields(QString("b1"))+QChar(',')+Session::getSelectFields(QString("b2")))->from(QString(SessionValue::TABLENAME),QString("b1"))->leftJoin(Session::TABLENAME,QString("b2"),QString("b1.session_id = b2.id"))->where(QString("b1.session_id=?"),sessionId)->where(QString("b1.key=?"),key)->execQuery();
if (res->next()){
SessionValue* b1 = SessionValue::getByRecord(res->record(),QString("b1"));
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
//throw new SqlException(sqlCon);
return nullptr;
}
QString SessionValue::getSelectFields (const QString& alias) {
if (alias.isEmpty()){
return QString("session_id as session_value__session_id,key as session_value__key,value as session_value__value") ;
} else {
return alias + QString(".session_id as ") + alias + QString("__session_id")+QChar(',')+alias + QString(".key as ") + alias + QString("__key")+QChar(',')+alias + QString(".value as ") + alias + QString("__value") ;
}

}
SessionValue* SessionValue::getByRecord (const QSqlRecord& record,const QString& alias) {
SessionValue* bean = new SessionValue ();
return bean->setValueInternal(record.value(alias + QString("__value")).toByteArray())->setSessionIdInternal(record.value(alias + QString("__session_id")).toString())->setKeyInternal(record.value(alias + QString("__key")).toString());
}
BeanQuery<SessionValue>* SessionValue::createQuery () {
return new BeanQuery<SessionValue> (sqlCon->buildQuery()) ;
}
QString SessionValue::getAllSelectFields (QString artistTableAlias) {
return SessionValue::getSelectFields(QString(artistTableAlias))+QChar(',')+Session::getSelectFields(QString("b2"));
}
void SessionValue::addRelatedTableJoins (BeanQuery<SessionValue>* query) {
query->leftJoin(Session::TABLENAME,QString("b2"),QString("b1.session_id = b2.id"));
}
QList<SessionValue*>* SessionValue::fetchList (QSqlQuery* res) {
QList<SessionValue*>* beans = new QList<SessionValue*>();
SessionValue* b1 = NULL;
while (res->next()){
b1 = SessionValue::getByRecord(res->record(),QString("b1"));
b1->loaded = true;
beans->append(b1);
if (!res->record().value(QString("b2__id")).isNull()){
Session* b2 = Session::getByRecord(res->record(),QString("b2"));
b1->session = b2;
}

}
return beans;
}
SessionValue* SessionValue::fetchOne (QSqlQuery* res) {
SessionValue* b1 = NULL;
if (res->next()){
b1 = SessionValue::getByRecord(res->record(),QString("b1"));
if (!res->record().value(QString("b2__id")).isNull()){
Session* b2 = Session::getByRecord(res->record(),QString("b2"));
b1->session = b2;
}

}

return b1;
}
void SessionValue::load () {
loaded = true;
SqlQuery* q = sqlCon->buildQuery();
QSqlQuery* res = q->select(Session::getSelectFields(QString("b2")))->from(SessionValue::TABLENAME ,QString("b1"))->leftJoin(Session::TABLENAME,QString("b2"),QString("b1.session_id = b2.id"))->where(QString("b1.session_id = ?"),getSessionId())->where(QString("b1.key = ?"),getKey())->execQuery();
if (res->next()){
do {
Session* b2 = Session::getByRecord(res->record(),QString("b2"));
if (this->session == NULL){
this->session = b2;
}

} while(res->next());
}

}
bool SessionValue::remove () {
SqlQuery* q = sqlCon->buildQuery()->deleteFrom(QString(SessionValue::TABLENAME))->where(QString("session_id = ?"),getSessionId())->where(QString("key = ?"),getKey());
return q->execute();
}
SessionValue* SessionValue::createNew () {
SessionValue* b = new SessionValue ();
b->setInsertNew();
return b;
}
bool SessionValue::exists (QString sessionId,QString key) {
SqlQuery* q = sqlCon->buildQuery();
q->select(QString("count(*)"))->from(QString(SessionValue::TABLENAME))->where(QString("session_id = ?"),sessionId)->where(QString("key = ?"),key);
return q->fetchInt()>0;
}
const char* SessionValue::TABLENAME = "session_value" ;
