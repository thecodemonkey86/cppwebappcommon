#include "session.h"
#include "basebean.h"
#include <QString>
#include <QVariant>
#include <QDate>
#include "nullable.h"
#include "beanquery.h"
#include "model/beans/cartentry.h"
#include "model/beans/sessionvalue.h"
Session::Session () {
loaded = false;
cartEntries = new QSet<CartEntry>();
sessionValues = new QSet<SessionValue>();
}
QString Session::getTableName () {
return QString(TABLENAME);
}
QString Session::getId () const {
return id;
}
QByteArray Session::getMd5Hash () const {
return md5Hash;
}
QDateTime Session::getExpirationDate () {
return expirationDate;
}
QList<CartEntry>* Session::getCartEntries () {
if (!loaded){
load();
}

QList<CartEntry>* result = new QList<CartEntry> ();
cartEntries->reserve(cartEntries->size());
typename QSet<CartEntry>::const_iterator i = cartEntries->constBegin();
while (i != cartEntries->constEnd()){
result->append(*i);
++i;
}
return result;
}
QList<SessionValue>* Session::getSessionValues () {
if (!loaded){
load();
}

QList<SessionValue>* result = new QList<SessionValue> ();
sessionValues->reserve(sessionValues->size());
typename QSet<SessionValue>::const_iterator i = sessionValues->constBegin();
while (i != sessionValues->constEnd()){
result->append(*i);
++i;
}
return result;
}
Session* Session::setExpirationDate (const QDateTime& expirationDate) {
this->expirationDateModified=true;
this->expirationDate=expirationDate;
return this;
}
Session* Session::setExpirationDateInternal (const QDateTime& expirationDate) {
this->expirationDate=expirationDate;
return this;
}
Session* Session::setId (const QString& id) {
if (!insert){
this->idModified = true;
this->_previousId = this->id;
}

this->id=id;
return this;
}
Session* Session::setIdInternal (const QString& id) {
this->id=id;
return this;
}
Session* Session::setMd5Hash (const QByteArray& md5Hash) {
if (!insert){
this->idModified = true;
this->_previousMd5Hash = this->md5Hash;
}

this->md5Hash=md5Hash;
return this;
}
Session* Session::setMd5HashInternal (const QByteArray& md5Hash) {
this->md5Hash=md5Hash;
return this;
}
QString Session::getInsertFields () {
return QString("id,md5_hash,expiration_date");
}
QString Session::getInsertValuePlaceholders () {
return QString("?,?,?");
}
QList<QVariant>* Session::getInsertParams () {
QList<QVariant>* params=new QList<QVariant>();
params->append(id);
params->append(md5Hash);
params->append(expirationDate);
return params;
}
QString Session::getUpdateFields (QList<QVariant>* params) {
QString query;
if (idModified){
params->append(id);
query += QString(",id=?");
params->append(md5Hash);
query += QString(",md5_hash=?");
}

if (expirationDateModified){
params->append(expirationDate);
query += QString(",expiration_date=?");
}

return query.mid(1);
}
QString Session::getUpdateCondition () {
return QString("id=? AND md5_hash=?");
}
QList<QVariant>* Session::getUpdateConditionParams () {
QList<QVariant>* params=new QList<QVariant>();
if (!idModified){
params->append(id);
params->append(md5Hash);
} else {
params->append(_previousId);
params->append(_previousMd5Hash);
}

return params;
}
Session* Session::getById (QString id,QByteArray md5Hash) {
SqlQuery*q = sqlCon->buildQuery();
QSqlQuery* res= q->select(Session::getSelectFields(QString("b1"))+QChar(',')+CartEntry::getSelectFields(QString("b2"))+QChar(',')+SessionValue::getSelectFields(QString("b3")))->from(QString(Session::TABLENAME),QString("b1"))->leftJoin(CartEntry::TABLENAME,QString("b2"),QString("b1.id = b2.session_id AND b1.md5_hash = b2.md5_hash"))->leftJoin(SessionValue::TABLENAME,QString("b3"),QString("b1.id = b3.session_id AND b1.md5_hash = b3.md5_hash"))->where(QString("b1.id=?"),id)->where(QString("b1.md5_hash=?"),md5Hash)->execQuery();
if (res->next()){
Session* b1 = Session::getByRecord(res->record(),QString("b1"));
b1->loaded = true;
do {
CartEntry* b2 = CartEntry::getByRecord(res->record(),QString("b2"));
if (!b1->cartEntries->contains(*b2)){
b1->cartEntries->insert(*b2);
}

SessionValue* b3 = SessionValue::getByRecord(res->record(),QString("b3"));
if (!b1->sessionValues->contains(*b3)){
b1->sessionValues->insert(*b3);
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
QString Session::getSelectFields (const QString& alias) {
if (alias.isEmpty()){
return QString("id as session__id,md5_hash as session__md5_hash,expiration_date as session__expiration_date") ;
} else {
return alias + QString(".id as ") + alias + QString("__id")+QChar(',')+alias + QString(".md5_hash as ") + alias + QString("__md5_hash")+QChar(',')+alias + QString(".expiration_date as ") + alias + QString("__expiration_date") ;
}

}
Session* Session::getByRecord (const QSqlRecord& record,const QString& alias) {
Session* bean = new Session ();
return bean->setExpirationDateInternal(record.value(alias + QString("__expiration_date")).toDateTime())->setIdInternal(record.value(alias + QString("__id")).toString())->setMd5HashInternal(record.value(alias + QString("__md5_hash")).toByteArray());
}
BeanQuery<Session>* Session::createQuery () {
return new BeanQuery<Session> (sqlCon->buildQuery()) ;
}
QString Session::getAllSelectFields (QString artistTableAlias) {
return Session::getSelectFields(QString(artistTableAlias))+QChar(',')+CartEntry::getSelectFields(QString("b2"))+QChar(',')+SessionValue::getSelectFields(QString("b3"));
}
void Session::addRelatedTableJoins (BeanQuery<Session>* query) {
query->leftJoin(CartEntry::TABLENAME,QString("b2"),QString("b1.id = b2.session_id AND b1.md5_hash = b2.md5_hash"))->leftJoin(SessionValue::TABLENAME,QString("b3"),QString("b1.id = b3.session_id AND b1.md5_hash = b3.md5_hash"));
}
QList<Session*>* Session::fetchList (QSqlQuery* res) {
QList<Session*>* beans = new QList<Session*>();
Session* b1 = NULL;
while (res->next()){
b1 = Session::getByRecord(res->record(),QString("b1"));
b1->loaded = true;
beans->append(b1);
if (!res->record().value(QString("b2__id")).isNull()){
CartEntry* b2 = CartEntry::getByRecord(res->record(),QString("b2"));
if (!b1->cartEntries->contains(*b2)){
b1->cartEntries->insert(*b2);
} else {
delete b2;
}

}

if (!res->record().value(QString("b3__id")).isNull()){
SessionValue* b3 = SessionValue::getByRecord(res->record(),QString("b3"));
if (!b1->sessionValues->contains(*b3)){
b1->sessionValues->insert(*b3);
} else {
delete b3;
}

}

}
return beans;
}
Session* Session::fetchOne (QSqlQuery* res) {
Session* b1 = NULL;
if (res->next()){
b1 = Session::getByRecord(res->record(),QString("b1"));
if (!res->record().value(QString("b2__id")).isNull()){
CartEntry* b2 = CartEntry::getByRecord(res->record(),QString("b2"));
if (!b1->cartEntries->contains(*b2)){
b1->cartEntries->insert(*b2);
} else {
delete b2;
}

}

if (!res->record().value(QString("b3__id")).isNull()){
SessionValue* b3 = SessionValue::getByRecord(res->record(),QString("b3"));
if (!b1->sessionValues->contains(*b3)){
b1->sessionValues->insert(*b3);
} else {
delete b3;
}

}

}

return b1;
}
void Session::load () {
loaded = true;
SqlQuery* q = sqlCon->buildQuery();
QSqlQuery* res = q->select(CartEntry::getSelectFields(QString("b2"))+QChar(',')+SessionValue::getSelectFields(QString("b3")))->from(Session::TABLENAME ,QString("b1"))->leftJoin(CartEntry::TABLENAME,QString("b2"),QString("b1.id = b2.session_id AND b1.md5_hash = b2.md5_hash"))->leftJoin(SessionValue::TABLENAME,QString("b3"),QString("b1.id = b3.session_id AND b1.md5_hash = b3.md5_hash"))->where(QString("b1.id = ?"),getId())->where(QString("b1.md5_hash = ?"),getMd5Hash())->execQuery();
if (res->next()){
do {
CartEntry* b2 = CartEntry::getByRecord(res->record(),QString("b2"));
if (!this->cartEntries->contains(*b2)){
this->cartEntries->insert(*b2);
}

SessionValue* b3 = SessionValue::getByRecord(res->record(),QString("b3"));
if (!this->sessionValues->contains(*b3)){
this->sessionValues->insert(*b3);
}

} while(res->next());
}

}
bool Session::remove () {
SqlQuery* q = sqlCon->buildQuery()->deleteFrom(QString(Session::TABLENAME))->where(QString("id = ?"),getId())->where(QString("md5_hash = ?"),getMd5Hash());
return q->execute();
}
Session* Session::createNew () {
Session* b = new Session ();
b->setInsertNew();
return b;
}
bool Session::exists (QString id,QByteArray md5Hash) {
SqlQuery* q = sqlCon->buildQuery();
q->select(QString("count(*)"))->from(QString(Session::TABLENAME))->where(QString("id = ?"),id)->where(QString("md5_hash = ?"),md5Hash);
return q->fetchInt()>0;
}
const char* Session::TABLENAME = "session" ;