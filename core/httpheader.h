#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <QString>
#include <QUrl>
#include "core/fastcgioutput.h"
#include "webappcommon_global.h"
#include <QNetworkCookie>
#include <memory>
#include "fcgio.h"
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT HttpHeader
{
protected:

    bool redirectFlag;
    unique_ptr<QNetworkCookie> sessionCookie;
    FCGX_Stream * out;

//    QList<QNetworkCookie> cookies;
public:
     HttpHeader(const FCGX_Request & request);
    static const QString CONTENT_TYPE_TEXT_HTML;
    static const QString CONTENT_TYPE_APPLICATION_JSON;
    static const QString CONTENT_TYPE_TEXT_XML;
    static const QString CONTENT_TYPE_BINARY;
//    void setCookie(const QString&name, const QString&value);
//    void clearCookie(const QString&name);
//    void parseCookies(const FCGX_Request & request);
//    QString cookieString(const QString&name) const;
    QString getSessionCookieValue() const;
    void clearSessionCookie();
    void setSessionCookie(const QString& value);
    void setContentType(const QString & contentType);
    void setRawHeader(const QString & header);
    void setRawHeader(const QString & key, const QString & value);
    void setRawHeader(const QString & key, int value);
    void setReturnCode(int code);
    void setReturnCode(int code, const QString & msg);
    void redirect(const QUrl & url);
    bool getRedirectFlag() const;
    void finish();
    bool isSessionCookieSet() const;
};

#endif // HTTPHEADER_H
