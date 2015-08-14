#ifndef UTIL_H
#define UTIL_H
#include "webappcommon_global.h"
#include <QString>

class WEBAPPCOMMONSHARED_EXPORT Util
{
public:
    Util();
    static QString randString(int length,const QString&chars="abcdefghijklmnoprstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") ;
};

#endif // UTIL_H
