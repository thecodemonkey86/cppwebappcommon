#ifndef HTMLRENDERABLE_H
#define HTMLRENDERABLE_H

#include <QString>
#include "fastcgicout.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT HtmlRenderable
{
public:
    HtmlRenderable();
    virtual void render() const =0 ;
};

#endif // HTMLRENDERABLE_H
