#include "jsonview.h"

JsonView::JsonView()
{

}


QString JsonView::getHttpContentType() const
{
    return HttpHeader::CONTENT_TYPE_APPLICATION_JSON;
}

