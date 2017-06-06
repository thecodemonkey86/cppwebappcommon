#ifndef HTMLUTIL_H
#define HTMLUTIL_H
#include "webappcommon_global.h"
#include <QDate>
#include <QString>
class WEBAPPCOMMONSHARED_EXPORT HtmlUtil
{
private:
    HtmlUtil();
public:
   static QString formatDate(const QDate & date, const QString & format, bool isSet);
};

#endif // HTMLUTIL_H
