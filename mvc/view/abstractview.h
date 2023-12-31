#pragma once

#include "webappcommon_global.h"
#include <core/fastcgioutput.h>
class ViewData;
class HttpHeader;
struct FCGX_Stream;

class WEBAPPCOMMONSHARED_EXPORT AbstractView
{
protected:
    HttpHeader * httpHeader;
    FCGX_Stream *out;
    bool autoSendHeaders;
public:
    AbstractView();
    AbstractView(const AbstractView &)= default;
    AbstractView& operator=(const AbstractView&) = default;
    virtual ~AbstractView() = default;
    virtual QString getHttpContentType() const=0;

    virtual void update(const ViewData &viewdata)=0;
    void setHttpHeader(HttpHeader *value);
    void setOutStream(FCGX_Stream *value);
    bool isAutoSendHeaders() const;

protected:
    template<class T>
    inline  void output(T value) const {
        FastCgiOutput::write(value,out);
    }
};

