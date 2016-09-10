#ifndef PAGEMVCMESSAGE_H
#define PAGEMVCMESSAGE_H

#include "mvc/mvcmessage.h"
#include "controller/abstractpagecontroller.h"
#include "webappcommon_global.h"
class AbstractPageController;

class WEBAPPCOMMONSHARED_EXPORT PageMvcMessage : public MvcMessage
{
    AbstractPageController * source;
public:
    PageMvcMessage();
    PageMvcMessage * setSource(AbstractPageController *value);
    AbstractPageController *getSource() const;
};

#endif // PAGEMVCMESSAGE_H
