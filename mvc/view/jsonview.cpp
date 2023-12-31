#include "jsonview.h"
#include <core/httpheader.h>
JsonView::JsonView()
{

}


QString JsonView::getHttpContentType() const
{
    return HttpHeader::CONTENT_TYPE_APPLICATION_JSON;
}

