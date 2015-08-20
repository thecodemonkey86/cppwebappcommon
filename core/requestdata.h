#ifndef REQUESTDATA_H
#define REQUESTDATA_H

#include <QString>
#include <QMap>
#include "core/requestparam.h"
#include "arrayrequestparam.h"
#include "fcgio.h"

class RequestData
{
private:
    RequestData();
    static QMap<QString, AbstractRequestParam*>* getParams;
    static QMap<QString, AbstractRequestParam*>* postParams;
    static QMap<QString, QString>* cookies;
public:

    static void parseParams(const QString&requestString, QMap<QString, AbstractRequestParam*>* params);
    static void parseGetParams();
    static void parsePostParams(const FCGX_Request & request);
    static void parseCookies(const FCGX_Request & request);
    static QString getString(const QString&name);
    static QString postString(const QString&name);
    static int getInt(const QString&name);
    static int postInt(const QString&name);
    static double postDouble(const QString&name);
    static bool postBool(const QString&name);
    static ArrayRequestParam * getArray(const QString&name);
    static bool isGetParamSet(const QString&name);
    static bool isPostParamSet(const QString&name);
    static QString cookieString(const QString&name);
    static QStringList cookieAsArray(const QString&name);
    static bool isCookieSet(const QString&name);
};

#endif // REQUESTDATA_H
