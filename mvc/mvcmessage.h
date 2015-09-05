#ifndef MVCMESSAGE_H
#define MVCMESSAGE_H
#include "model/sessiondata.h"

class MvcMessage
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
