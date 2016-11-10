#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <QString>
#include <QUrl>
#include "fastcgicout.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT HttpHeader
{
protected:

    bool redirectFlag;
public:
     HttpHeader();
    static const QString CONTENT_TYPE_TEXT_HTML;
    void setCookie(const QString&name, const QString&value);
    void setContentType(const QString & contentType);
    void setReturnCode(int code);
    void setReturnCode(int code, const QString & msg);
    void redirect(const QUrl & url);
    bool getRedirectFlag() const;
    void finish();
};

#endif // HTTPHEADER_H
