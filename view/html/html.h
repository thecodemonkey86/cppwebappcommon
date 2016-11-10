#ifndef HTML_H
#define HTML_H
#include "htmlselect.h"
#include "htmlselectoption.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT Html
{
protected :
     Html();
public:

    static HtmlSelect select();
    static HtmlSelectOption option(const QString&value, const QString&display);
};

#endif // HTML_H