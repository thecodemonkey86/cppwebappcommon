#include "ajaxhtmlview.h"


QString AjaxHtmlView::getHttpContentType() const
{
    return HttpHeader::CONTENT_TYPE_TEXT_HTML;
}
