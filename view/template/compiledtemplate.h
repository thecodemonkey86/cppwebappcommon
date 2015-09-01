#ifndef COMPILEDTEMPLATE_H
#define COMPILEDTEMPLATE_H

#include "abstracttemplate.h"

class CompiledTemplate : public AbstractTemplate
{
public:
    CompiledTemplate();
     virtual void render()=0;
};

#endif // COMPILEDTEMPLATE_H
