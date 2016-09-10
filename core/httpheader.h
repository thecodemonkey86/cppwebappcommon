#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <QString>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT HttpHeader
{
protected:
    HttpHeader();
public:
    static const QString CONTENT_TYPE_TEXT_HTML;
    static void setCookie(const QString&name, const QString&value);
    static void setReturnCode(int code);
};

#endif // HTTPHEADER_H
