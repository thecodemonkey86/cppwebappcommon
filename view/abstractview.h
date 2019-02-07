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
public:
    AbstractView();
    virtual ~AbstractView();
    virtual QString getHttpContentType() const=0;
    virtual void setHeaders();
    virtual void update(unique_ptr<MvcMessage>)=0;
    void setHttpHeader(HttpHeader *value);
};

#endif // ABSTRACTVIEW_H
