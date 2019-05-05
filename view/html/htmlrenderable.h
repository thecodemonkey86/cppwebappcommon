#ifndef HTMLRENDERABLE_H
#define HTMLRENDERABLE_H

#include <QString>
#include "core/fastcgioutput.h"
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT HtmlRenderable
{
    FCGX_Stream * out;
protected:
    template<class T>
    inline  void output(T value) const {
        FastCgiOutput::write(value,out);
    }
public:
    HtmlRenderable();
    HtmlRenderable(const HtmlRenderable & )=default;
    virtual ~HtmlRenderable()=default;
    virtual void render() const =0 ;
    void setOutStream(FCGX_Stream *value);
};

#endif // HTMLRENDERABLE_H
