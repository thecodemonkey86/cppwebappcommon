#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H
#include "webappcommon_global.h"
#include "mvc/model/viewdata.h"
#include <memory>
#include <core/httpheader.h>
using namespace std;

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

    virtual void update(unique_ptr<ViewData>)=0;
    void setHttpHeader(HttpHeader *value);
    void setOutStream(FCGX_Stream *value);
    bool isAutoSendHeaders() const;

protected:
    template<class T>
    inline  void output(T value) const {
        FastCgiOutput::write(value,out);
    }
};

#endif // ABSTRACTVIEW_H
