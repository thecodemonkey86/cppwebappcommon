#include "abstractview.h"

void AbstractView::setHttpHeader(HttpHeader *value)
{
    httpHeader = value;
}

void AbstractView::setOutStream(FCGX_Stream *value)
{
    out = value;
}

AbstractView::AbstractView()
{
    autoSendHeaders = true;
}

bool AbstractView::isAutoSendHeaders() const
{
    return autoSendHeaders;
}


