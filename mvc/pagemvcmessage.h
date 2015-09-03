#ifndef PAGEMVCMESSAGE_H
#define PAGEMVCMESSAGE_H

#include "mvc/mvcmessage.h"
#include "controller/abstractpagecontroller.h"

class AbstractPageController;

class PageMvcMessage : public MvcMessage
{
    AbstractPageController * source;
public:
    PageMvcMessage(AbstractPageController * source);
};

#endif // PAGEMVCMESSAGE_H
