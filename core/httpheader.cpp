#include "httpheader.h"
#include <iostream>

using namespace std;

bool HttpHeader::getRedirectFlag() const
{
    return redirectFlag;
}

void HttpHeader::finish()
{
    cout << "\r\n";
}

HttpHeader::HttpHeader()
{

}

void HttpHeader::setCookie(const QString &name, const QString &value)
{
    FastCgiCout::write("Set-Cookie: ");
    FastCgiCout::write(name);
    FastCgiCout::write("=");
    FastCgiCout::write(value);
    FastCgiCout::write("\r\n");
}

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

const QString HttpHeader::CONTENT_TYPE_TEXT_HTML("text/html; charset=UTF-8");
const QString HttpHeader::CONTENT_TYPE_BINARY("application/octet-stream");
const QString HttpHeader::CONTENT_TYPE_TEXT_XML("text/xml; charset=UTF-8");
