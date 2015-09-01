#ifndef REQUESTDATA_H
#define REQUESTDATA_H

#include <QString>
#include <QMap>
#include "core/requestparam.h"
#include "arrayrequestparam.h"
#include "fcgio.h"
#include <QUrl>

class RequestData
{
private:

    QMap<QString, AbstractRequestParam*>* getParams;
    QMap<QString, AbstractRequestParam*>* postParams;
    QMap<QString, QString>* cookies;
    void parseParams(const QString&requestString, QMap<QString, AbstractRequestParam*>* params);
    void parseGetParams(const QUrl& url);
    void parsePostParams(const FCGX_Request & request);
    void parseCookies(const FCGX_Request & request);
public:
 RequestData(const FCGX_Request & request, const QUrl &url);

    QString getString(const QString&name);
    QString postString(const QString&name);
    int getInt(const QString&name);
    int postInt(const QString&name);
    double postDouble(const QString&name);
    bool postBool(const QString&name);
    ArrayRequestParam * getArray(const QString&name);
    bool isGetParamSet(const QString&name);
    bool isPostParamSet(const QString&name);
    QString cookieString(const QString&name);
    QStringList cookieAsArray(const QString&name);
    bool isCookieSet(const QString&name);
};

#endif // REQUESTDATA_H
