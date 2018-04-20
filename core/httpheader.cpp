#include "httpheader.h"
#include "exception/qtexception.h"
#include <iostream>
#include <QNetworkCookie>
#include "sessiondata.h"

using namespace QtCommon2;
using namespace std;

bool HttpHeader::getRedirectFlag() const
{
    return redirectFlag;
}

void HttpHeader::finish()
{

    if(sessionCookie != nullptr) {
        FastCgiCout::write("Set-Cookie: ");
        FastCgiCout::write(sessionCookie->toRawForm());
        FastCgiCout::write("\r\n");
    }


    cout << "\r\n";
}

bool HttpHeader::isSessionCookieSet() const
{
    return sessionCookie != nullptr;
}



HttpHeader::HttpHeader(const FCGX_Request & request)
{
    this->redirectFlag = false;
    sessionCookie = nullptr;
    char * cookieStr = FCGX_GetParam("HTTP_COOKIE", request.envp);
    if(cookieStr != nullptr) {
        auto cookies = QNetworkCookie::parseCookies(QByteArray::fromRawData(cookieStr, static_cast<int>(strlen(cookieStr))));
        for(auto c : cookies) {
            if(c.name() == SessionData::getSessionCookieName().toLatin1()) {
                sessionCookie = make_unique<QNetworkCookie>(c);
                break;
            }
        }
    }

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

void HttpHeader::setSessionCookie(const QString &value)
{
    sessionCookie = make_unique<QNetworkCookie>(SessionData::getSessionCookieName().toLatin1(), value.toLatin1() );
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
    FastCgiCout::write( "Content-Type: ");
    FastCgiCout::write(contentType);
    FastCgiCout::write("\r\n");
}

void HttpHeader::setRawHeader(const QString &header)
{
    FastCgiCout::write(header);
    FastCgiCout::write("\r\n");
}

void HttpHeader::setRawHeader(const QString &key, const QString &value)
{
    FastCgiCout::write(key);
    FastCgiCout::write(':');
    FastCgiCout::write(value);
    FastCgiCout::write("\r\n");
}

void HttpHeader::setRawHeader(const QString &key, int value)
{
   FastCgiCout::write(key);
   FastCgiCout::write(':');
   FastCgiCout::write( QString::number(value));
   FastCgiCout::write("\r\n");
}

void HttpHeader::setReturnCode(int code)
{
    FastCgiCout::write("Status: ");
    FastCgiCout::write(QString::number(code));
    FastCgiCout::write("\r\n");

}

void HttpHeader::setReturnCode(int code, const QString &msg)
{
    FastCgiCout::write("Status: ");
    FastCgiCout::write(QString::number(code));
    FastCgiCout::write(QChar(' '));
    FastCgiCout::write(msg);
    FastCgiCout::write("\r\n");
}

void HttpHeader::redirect(const QUrl &url)
{
    this->redirectFlag = true;
    FastCgiCout::write( "Location: ");
    FastCgiCout::write(url.toString(QUrl::None));
    FastCgiCout::write("\r\n");
}
/*
void HttpHeader::parseCookies(const FCGX_Request & request)
{
    char * cookieStr = FCGX_GetParam("HTTP_COOKIE", request.envp);
    auto cookies = QNetworkCookie::parseCookies(QByteArray::fromRawData(cookieStr, strlen(cookieStr)));
    for(auto c : cookies) {
        if(c.name() == SessionData::getSessionCookieName().toLatin1()) {
            sessionCookie = c;
            break;
        }
    }
}

QString HttpHeader::cookieString(const QString &name) const
{
    for(const QNetworkCookie & c : cookies) {
        if(c.name() == name.toLatin1()) {
            return QString::fromLatin1(c.value());
        }
    }
    throw QtException(QStringLiteral("cookie not set"));
}
*/
const QString HttpHeader::CONTENT_TYPE_TEXT_HTML("text/html; charset=UTF-8");
const QString HttpHeader::CONTENT_TYPE_BINARY("application/octet-stream");
const QString HttpHeader::CONTENT_TYPE_TEXT_XML("text/xml; charset=UTF-8");
const QString HttpHeader::CONTENT_TYPE_APPLICATION_JSON("application/json; charset=UTF-8");
