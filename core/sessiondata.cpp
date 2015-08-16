#include "sessiondata.h"
#include "beanquery.h"
#include "model/beans/session.h"
#include <QCryptographicHash>
#include "util/util.h"
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/httpheader.h"


SessionData::SessionData()
{

}

SessionData::~SessionData()
{

}

void SessionData::init()
{
    if (RequestData::isCookieSet(sessCookieName)) {

        BeanQuery<Session> * query = Session::createQuery()
                ->select()
                ->where("id=?", RequestData::cookieString(sessCookieName))
                ->andWhere("md5_hash=?",QCryptographicHash::hash(ServerData:: getIp().toUtf8(),QCryptographicHash::Md5))
                ->andWhere("expiration_date>now()");

        Session * existing = query->queryOne();
        if (existing != NULL) {
            SessionData::session = existing;
            HttpHeader::setCookie(sessCookieName,session->getId());
            return;
        }
    }
    SessionData::session = Session::createNew()
            ->setId(Util::randString(64))
            ->setMd5Hash(QCryptographicHash::hash(ServerData::getIp().toUtf8(),QCryptographicHash::Md5))
            ->setExpirationDate(QDateTime::currentDateTime());
    SessionData::session->save();
    HttpHeader::setCookie(sessCookieName,session->getId());
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


Session* SessionData::session = NULL;
const char * SessionData::sessCookieName="PHPSESSID";
