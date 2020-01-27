#include "httpheader.h"
#include "exception/qtexception.h"
#include <QNetworkCookie>
#include "sessiondata.h"
#ifdef QT_DEBUG
#include <QDebug>
#endif
using namespace QtCommon2;
using namespace std;

bool HttpHeader::getRedirectFlag() const
{
    return redirectFlag;
}

void HttpHeader::finish()
{

    if(sessionCookie != nullptr) {
        FastCgiOutput::write("Set-Cookie: ",out);
        FastCgiOutput::write(sessionCookie->toRawForm(),out);
        FastCgiOutput::write("\r\n",out);
    }


    FastCgiOutput::write("\r\n",out);
}



HttpHeader::HttpHeader(const FCGX_Request & request)
{
  this->out = request.out;
  this->redirectFlag = false;
    sessionCookie = nullptr;


}

QString HttpHeader::getSessionCookieValue() const
{
    if(sessionCookie == nullptr) {
        throw QtException("session cookie is not set");
    }
    return QUrl::fromPercentEncoding(sessionCookie->value());
}

void HttpHeader::clearSessionCookie()
{
    sessionCookie = nullptr;
}

void HttpHeader::setSessionCookie(const QString &value,const QString&domain, const QDateTime &validUntil)
{
    sessionCookie = make_unique<QNetworkCookie>(SessionData::getSessionCookieName().toLatin1(), value.toLatin1() );
    sessionCookie->setExpirationDate(validUntil);
    sessionCookie->setHttpOnly(true);
    sessionCookie->setPath("/");
    sessionCookie->setDomain(domain);
}
/*
void HttpHeader::setCookie(const QString &name, const QString &value)
{
   // this->cookies.insert(name,value);
}

bool HttpHeader::isCookieSet(const QString &name) const
{
  //  return cookies.contains(name);
}


void HttpHeader::clearCookie(const QString &name)
{
   // this->cookies.deleteCookie(this->cookies. name);
}
*/
void HttpHeader::setContentType(const QString &contentType)
{
    FastCgiOutput::write( "Content-Type: ",out);
    FastCgiOutput::write(contentType,out);
    FastCgiOutput::write("\r\n",out);
}

void HttpHeader::setRawHeader(const QString &header)
{
    FastCgiOutput::write(header,out);
    FastCgiOutput::write("\r\n",out);
}

void HttpHeader::setRawHeader(const QString &key, const QString &value)
{
    FastCgiOutput::write(key,out);
    FastCgiOutput::write(':',out);
    FastCgiOutput::write(value,out);
    FastCgiOutput::write("\r\n",out);
}

void HttpHeader::setRawHeader(const QString &key, int value)
{
   FastCgiOutput::write(key,out);
   FastCgiOutput::write(':',out);
   FastCgiOutput::write( QString::number(value),out);
   FastCgiOutput::write("\r\n",out);
}

void HttpHeader::setReturnCode(int code)
{
    FastCgiOutput::write("Status: ",out);
    FastCgiOutput::write(QString::number(code),out);
    FastCgiOutput::write("\r\n",out);

}

void HttpHeader::setReturnCode(int code, const QString &msg)
{
    FastCgiOutput::write("Status: ",out);
    FastCgiOutput::write(QString::number(code),out);
    FastCgiOutput::write(' ',out);
    FastCgiOutput::write(msg,out);
    FastCgiOutput::write("\r\n",out);
}

void HttpHeader::redirect(const QUrl &url)
{
    this->redirectFlag = true;
    FastCgiOutput::write( "Location: ",out);
    FastCgiOutput::write(url.toString(QUrl::None),out);
    FastCgiOutput::write("\r\n",out);
}

const QString HttpHeader::CONTENT_TYPE_TEXT_HTML("text/html; charset=UTF-8");
const QString HttpHeader::CONTENT_TYPE_TEXT_PLAIN("text/plain; charset=UTF-8");
const QString HttpHeader::CONTENT_TYPE_BINARY("application/octet-stream");
const QString HttpHeader::CONTENT_TYPE_TEXT_XML("text/xml; charset=UTF-8");
const QString HttpHeader::CONTENT_TYPE_APPLICATION_JSON("application/json; charset=UTF-8");
