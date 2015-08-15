#include "sessiondata.h"
#include "beanquery.h"
#include "model/beans/session.h"

SessionData::SessionData()
{

}

SessionData::~SessionData()
{

}

void SessionData::init(const QString &sessid)
{
    SessionData::sessid = sessid;
}

void SessionData::set(const QString &name, const QByteArray &value)
{
    BeanQuery<Session> * query = Session::createQuery()
            ->select()
            ->where("id=?", sessid)
            ->where("expiration_date>now()");

    Session * existing = query->queryOne();
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
}

