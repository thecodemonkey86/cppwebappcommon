#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H
#include "webappcommon_global.h"
#include "mvc/mvcmessage.h"
#include <memory>
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT AbstractView
{
protected:
    HttpHeader * httpHeader;
    FCGX_Stream *out;
    bool autoSendHeaders;
public:
    AbstractView();
    virtual ~AbstractView() = default;
    virtual QString getHttpContentType() const=0;

    virtual void update(unique_ptr<MvcMessage>)=0;
    void setHttpHeader(HttpHeader *value);
    void setOutStream(FCGX_Stream *value);
    bool getAutoSendHeaders() const;

protected:
    template<class T>
    inline  void output(T value) const {
        FastCgiOutput::write(value,out);
    }
};

#endif // ABSTRACTVIEW_H
