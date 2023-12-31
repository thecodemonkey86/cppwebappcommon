#pragma once


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

