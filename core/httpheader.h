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

/**
 * @brief class provides methods to set HTTP headers in FastCGI connection
 */
class WEBAPPCOMMONSHARED_EXPORT HttpHeader
{
protected:

    bool redirectFlag;
    unique_ptr<QNetworkCookie> sessionCookie;
    FCGX_Stream * out;

//    QList<QNetworkCookie> cookies;
public:

  /**
      * @brief constructor parses the session cookie from FastCGI request
      * @param request
      */
     HttpHeader(const FCGX_Request & request);
    static const QString CONTENT_TYPE_TEXT_HTML;
    static const QString CONTENT_TYPE_APPLICATION_JSON;
    static const QString CONTENT_TYPE_TEXT_XML;
    static const QString CONTENT_TYPE_BINARY;

    QString getSessionCookieValue() const;
    void clearSessionCookie();

    /**
     * @brief sets the session ID, class QNetworkCookie is used internally
     * @param session ID
     */
    void setSessionCookie(const QString& value, const QString &domain, const QDateTime & validUntil);

    /**
     * @brief sets the HTTP header "Content-Type: <MIME type>"
     * @param contentType
     */
    void setContentType(const QString & contentType);

    /**
     * @brief sets a custom HTTP header in raw form
     * @param header
     */
    void setRawHeader(const QString & header);

    /**
     * @brief sets a custom HTTP header "<key>: <value>"
     * @param header
     */
    void setRawHeader(const QString & key, const QString & value);

    /**
     * @brief sets a custom HTTP header "<key>: <integer value>"
     * @param header
     */
    void setRawHeader(const QString & key, int value);

    /**
     * @brief setReturnCode
     * @param the HTTP return code
     */
    void setReturnCode(int code);

    /**
     * @brief setReturnCode
     * @param the HTTP return code
     * @param the text, e.g. the string "OK" in HTTP/1.1 200 OK
     */
    void setReturnCode(int code, const QString & msg);

    /**
     * @brief sets the HTTP header "Location: <URL>" and sends the header
     * @param url
     */
    void redirect(const QUrl & url);
    bool getRedirectFlag() const;

    /**
     * @brief sends the header by adding CRLF
     */
    void finish();
//    bool isSessionCookieSet() const;
    QByteArray getRequestedSessionId() const;
    bool hasRequestSessionId() const;
};

#endif // HTTPHEADER_H
