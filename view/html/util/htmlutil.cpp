#include "htmlutil.h"

HtmlUtil::HtmlUtil()
{

}

QString HtmlUtil::formatDate(const QDate &date, const QString &format, bool isSet)
{
    return isSet ? date.toString(format).toHtmlEscaped() : QStringLiteral("");
}
