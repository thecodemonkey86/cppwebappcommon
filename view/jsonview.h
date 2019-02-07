#ifndef JSONVIEW_H
#define JSONVIEW_H

#include "abstractview.h"

#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT JsonView : public AbstractView
{
public:
    JsonView();

    // AbstractView interface
public:
    virtual QString getHttpContentType() const override;
};

#endif // JSONVIEW_H
