#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <QString>

class HttpHeader
{
protected:
    HttpHeader();
public:

    static void setCookie(const QString&name, const QString&value);
};

#endif // HTTPHEADER_H
