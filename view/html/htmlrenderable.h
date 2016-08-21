#ifndef HTMLRENDERABLE_H
#define HTMLRENDERABLE_H

#include <QString>
#include "fastcgicout.h"

class HtmlRenderable
{
protected:
    FastCgiCout out;
public:
    HtmlRenderable();
    virtual void render() const =0 ;
};

#endif // HTMLRENDERABLE_H
