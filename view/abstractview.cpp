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

}



void AbstractView::setHeaders()
{

}

