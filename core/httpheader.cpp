#include "httpheader.h"
#include <iostream>

HttpHeader::HttpHeader()
{

}

void HttpHeader::setCookie(const QString &name, const QString &value)
{
    std::cout<< "Set-Cookie: "<<name.toUtf8().data()<<"="<<value.toUtf8().data()<<"\r\n";
}

