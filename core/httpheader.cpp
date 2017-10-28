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
    FastCgiCout out;
    out<< "Set-Cookie: "<<name<<"="<<value<<"\r\n";
}

void HttpHeader::setContentType(const QString &contentType)
{
    FastCgiCout out;
    out<< "Content-Type: "<<contentType<<"\r\n";
}

void HttpHeader::setRawHeader(const QString &header)
{
    FastCgiCout out;
    out<<header<<"\r\n";
}

void HttpHeader::setRawHeader(const QString &key, const QString &value)
{
    FastCgiCout out;
    out<<key<<':'<<value<<"\r\n";
}

void HttpHeader::setRawHeader(const QString &key, int value)
{
    FastCgiCout out;
    out<<key<<':'<< QString::number(value)<<"\r\n";
}

void HttpHeader::setReturnCode(int code)
{
    FastCgiCout out;
    out<<"Status: "<<QString::number(code)<<"\r\n";

}

void HttpHeader::setReturnCode(int code, const QString &msg)
{
    FastCgiCout out;
    out<<"Status: "<<QString::number(code)<<QChar(' ')<<msg<<"\r\n";
}

void HttpHeader::redirect(const QUrl &url)
{
    FastCgiCout out;
    this->redirectFlag = true;
    out<< "Location: "<<url.toString(QUrl::None)<<"\r\n";
}

const QString HttpHeader::CONTENT_TYPE_TEXT_HTML("text/html; charset=UTF-8");
const QString HttpHeader::CONTENT_TYPE_BINARY("application/octet-stream");
const QString HttpHeader::CONTENT_TYPE_TEXT_XML("text/xml; charset=UTF-8");
