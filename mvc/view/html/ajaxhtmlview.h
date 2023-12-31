#pragma once


#include <mvc/view/abstractview.h>



class WEBAPPCOMMONSHARED_EXPORT AjaxHtmlView : public AbstractView
{
public:
    AjaxHtmlView() = default;
    virtual ~AjaxHtmlView() override = default ;

public:
    virtual QString getHttpContentType() const override;
};

