#include "sessiondata.h"
#include "beanquery.h"
#include "model/beans/session.h"
#include <QCryptographicHash>
#include "util/util.h"

SessionData::SessionData()
{

}

SessionData::~SessionData()
{

}

void SessionData::init(const QString &sessid,const QString &ip)
{
    BeanQuery<Session> * query = Session::createQuery()
            ->select()
            ->where("id=?", sessid)
            ->andWhere("md5_hash=?",QCryptographicHash::hash(ip.toUtf8(),QCryptographicHash::Md5))
            ->andWhere("expiration_date>now()");

    Session * existing = query->queryOne();
    if (existing != NULL) {
        SessionData::session = existing;
    } else {
       // Session::createNew()->setId(Util::randString(64))->set
    }
}

/*void SessionData::set(const QString &name, const QByteArray &value)
{

    if (existing != NULL) {
        QList<SessionValue>* values= existing->getSessionValues();
        foreach (SessionValue v, *values) {
            if (v.getKey() == name) {
                v.setValue(value);
                v.save();
                return;
            }
        }
        SessionValue::createNew()->setSessionId(sessid)->setKey(name)->setValue(value)->save();
    }
}*/



