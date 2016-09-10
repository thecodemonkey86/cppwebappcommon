#ifndef MVCMESSAGE_H
#define MVCMESSAGE_H
#include "core/sessiondata.h"
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT MvcMessage
{
protected:
    SessionData *sessionData;
public:
    MvcMessage();
    virtual ~ MvcMessage();
    SessionData *getSessionData() const;
    MvcMessage* setSessionData(SessionData *value);
};

#endif // MVCMESSAGE_H
