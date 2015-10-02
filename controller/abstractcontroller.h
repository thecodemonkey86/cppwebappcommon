#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "view/abstractview.h"
#include "webappcommon_global.h"
#include <memory>

using namespace std;

class WEBAPPCOMMONSHARED_EXPORT AbstractController
{
public:
    AbstractController();
    ~AbstractController();
    virtual void registerView(const shared_ptr<AbstractView>& view);
    shared_ptr<AbstractView> getView() const;

protected: shared_ptr<AbstractView> view;


};

#endif // ABSTRACTCONTROLLER_H
