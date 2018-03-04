#ifndef REQUESTDATA_H
#define REQUESTDATA_H

#include <QString>
#include <QHash>
#include "core/requestparam.h"
#include "arrayrequestparam.h"
#include "fcgio.h"
#include <QUrl>

class WEBAPPCOMMONSHARED_EXPORT RequestData
{
private:

    QHash<QString, AbstractRequestParam*> getParams;
    QHash<QString, AbstractRequestParam*> postParams;
    QHash<QString, QString> cookies;
    void parseParams(const QString&requestString, QHash<QString, AbstractRequestParam*>& params);
    void parseGetParams(const QUrl& url);
    void parsePostParams(const FCGX_Request & request);
    void parseCookies(const FCGX_Request & request);
public:
 RequestData(const FCGX_Request & request, const QUrl &url);
    ~RequestData();
    QString getString(const QString&name) const;
    QString postString(const QString&name, bool required = false) const;
    int getInt(const QString&name) const;
    int postInt(const QString&name) const;
    double postDouble(const QString&name) const;
    double getDouble(const QString&name) const;
    bool postBool(const QString&name) const;
    ArrayRequestParam * getArray(const QString&name) const;
    bool isGetParamSet(const QString&name) const;
    bool isPostParamSet(const QString&name) const;
    QString cookieString(const QString&name) const;
    QStringList cookieAsArray(const QString&name) const;
    bool isCookieSet(const QString&name) const;
};

#endif // REQUESTDATA_H
