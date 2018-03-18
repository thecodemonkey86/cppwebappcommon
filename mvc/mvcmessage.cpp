#include "mvcmessage.h"
#include <QDebug>



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
    //qDebug()<<"destr mvc";
}

