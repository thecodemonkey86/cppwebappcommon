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
    QString getString(const QString&name);
    QString postString(const QString&name, bool required = false);
    int getInt(const QString&name);
    int postInt(const QString&name);
    double postDouble(const QString&name);
    double getDouble(const QString&name);
    bool postBool(const QString&name);
    ArrayRequestParam * getArray(const QString&name);
    bool isGetParamSet(const QString&name);
    bool isPostParamSet(const QString&name);
    QString cookieString(const QString&name);
    QStringList cookieAsArray(const QString&name);
    bool isCookieSet(const QString&name);
};

#endif // REQUESTDATA_H
