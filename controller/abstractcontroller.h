#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "view/abstractview.h"
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT AbstractController
{
public:
    AbstractController();
    ~AbstractController();
    virtual void registerView(AbstractView * view);
protected: AbstractView * view;


};

#endif // ABSTRACTCONTROLLER_H
