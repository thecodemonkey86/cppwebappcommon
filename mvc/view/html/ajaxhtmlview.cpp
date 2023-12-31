#include "ajaxhtmlview.h"
#include <core/httpheader.h>

QString AjaxHtmlView::getHttpContentType() const
{
    return HttpHeader::CONTENT_TYPE_TEXT_HTML;
}
