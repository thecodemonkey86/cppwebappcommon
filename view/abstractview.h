#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT AbstractView
{
public:
    AbstractView();
    ~AbstractView();
    virtual void update()=0;
};

#endif // ABSTRACTVIEW_H
