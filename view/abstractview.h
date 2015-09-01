#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H
#include "webappcommon_global.h"
#include "mvc/mvcmessage.h"

class WEBAPPCOMMONSHARED_EXPORT AbstractView
{
public:
    AbstractView();
    ~AbstractView();
    virtual void update(MvcMessage*)=0;
};

#endif // ABSTRACTVIEW_H
