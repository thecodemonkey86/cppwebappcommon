#include "abstractview.h"
#include <core/httpheader.h>
void AbstractView::setHttpHeader(HttpHeader *value)
{
    httpHeader = value;
}

void AbstractView::setOutStream(FCGX_Stream *value)
{
    out = value;
}

AbstractView::AbstractView() : autoSendHeaders(true),httpHeader(nullptr),out(nullptr)
{
}

bool AbstractView::isAutoSendHeaders() const
{
    return autoSendHeaders;
}


