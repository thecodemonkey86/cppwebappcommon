#include "mvcmessage.h"




SessionData *MvcMessage::getSessionData() const
{
    return sessionData;
}

MvcMessage *MvcMessage::setSessionData(SessionData *value)
{
    sessionData = value;
    return this;
}


MvcMessage::MvcMessage()
{
    
}

MvcMessage::~MvcMessage()
{
    
}

