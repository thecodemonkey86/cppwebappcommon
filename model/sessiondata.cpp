#include "sessiondata.h"
#include "beanquery.h"
#include <QCryptographicHash>
#include "util/util.h"
#include "core/requestdata.h"
#include "core/serverdata.h"
#include "core/httpheader.h"
#include "model/beans/session.h"
#include "core/httpheader.h"

Session *SessionData::getSession()
{
    return session;
}


SessionData::SessionData(const QString &sessionId, const QString &ipAddress)
{
    BeanQuery<Session> * query = Session::createQuery()->select()->where("id=?",sessionId)->andWhere("md5_hash=?", QCryptographicHash::hash(ipAddress.toUtf8(),QCryptographicHash::Md5));

    this->session = query->queryOne();
    if (this->session == nullptr) {
        this->session = Session::createNew()
            ->setId(Util::randString(64))
            ->setMd5Hash(QCryptographicHash::hash(ipAddress.toUtf8(),QCryptographicHash::Md5))
            ->setExpirationDate(QDateTime::currentDateTime().addDays(1));
        this->session->save();
    }
    HttpHeader::setCookie(sessCookieName,session->getId());

    delete query;
}

SessionData::~SessionData()
{
    delete this->session;
}
const char *SessionData::getSessionCookieName()
{
    return sessCookieName;
}


/*void SessionData::init()
{
    qDebug()<<"cookie set:"<<RequestData::isCookieSet(sessCookieName);
    if (RequestData::isCookieSet(sessCookieName)) {

        BeanQuery<Session> * query = Session::createQuery()
                ->select()
                ->where("b1.id=?", RequestData::cookieString(sessCookieName))
                ->andWhere("b1.md5_hash=?",QCryptographicHash::hash(ServerData:: getIp().toUtf8(),QCryptographicHash::Md5))
                ->andWhere("b1.expiration_date>now()");

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
            ->setExpirationDate(QDateTime::currentDateTime().addDays(1));
    SessionData::session->save();

    HttpHeader::setCookie(sessCookieName,session->getId());
}

void SessionData::set(const QString &name, const QByteArray &value)
{

    QList<SessionValue*>* values= session->getSessionValues();
    foreach (SessionValue* v, *values) {
        if (v->getKey() == name) {
            v->setValue(value);
            v->save();
            return;
        }
    }
    SessionValue::createNew()->setSessionId(session->getId())
            ->setMd5Hash(session->getMd5Hash())
            ->setKey(name)
            ->setValue(value)
            ->save();
}

bool SessionData::existsValue(const QString &name)
{
    QList<SessionValue*>* values= session->getSessionValues();
    foreach (SessionValue* v, *values) {
         if (v->getKey() == name) {
             return true;
         }
    }
    return false;
}

QString SessionData::stringValue(const QString &name)
{
    QList<SessionValue*>* values= session->getSessionValues();
    foreach (SessionValue* v, *values) {
         if (v->getKey() == name) {
             return QString::fromUtf8(v->getValue().val());
         }
    }
    throw QtException("no such value");
}


Session* SessionData::session = NULL;*/
const char * SessionData::sessCookieName="PHPSESSID";
