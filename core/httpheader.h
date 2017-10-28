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
    static const QString CONTENT_TYPE_TEXT_XML;
    static const QString CONTENT_TYPE_BINARY;
    void setCookie(const QString&name, const QString&value);
    void setContentType(const QString & contentType);
    void setRawHeader(const QString & header);
    void setRawHeader(const QString & key, const QString & value);
    void setRawHeader(const QString & key, int value);
    void setReturnCode(int code);
    void setReturnCode(int code, const QString & msg);
    void redirect(const QUrl & url);
    bool getRedirectFlag() const;
    void finish();
};

#endif // HTTPHEADER_H
