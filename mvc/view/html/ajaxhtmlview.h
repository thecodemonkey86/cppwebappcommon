#ifndef AJAXHTMLVIEW_H
#define AJAXHTMLVIEW_H

#include <mvc/view/abstractview.h>



class WEBAPPCOMMONSHARED_EXPORT AjaxHtmlView : public AbstractView
{
public:
    AjaxHtmlView() = default;
    virtual ~AjaxHtmlView() override = default ;

public:
    virtual QString getHttpContentType() const override;
};

#endif // AJAXHTMLVIEW_H
