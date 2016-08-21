#include "httpheader.h"
#include <iostream>

using namespace std;

HttpHeader::HttpHeader()
{

}

void HttpHeader::setCookie(const QString &name, const QString &value)
{
    cout<< "Set-Cookie: "<<name.toUtf8().data()<<"="<<value.toUtf8().data()<<"\r\n";
}

void HttpHeader::setReturnCode(int code)
{
    cout<<"Status: "<<QString::number(code).toUtf8().data()<<"\r\n\r\n";

}

const QString HttpHeader::CONTENT_TYPE_TEXT_HTML("text/html; charset=UTF-8");
