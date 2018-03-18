#include "util.h"

Util::Util()
{

}

QString Util::randString( int length,const QString &chars)
{
    QString s(length, QChar('0'));

    for(int i=0;i<length;i++) {
        s[i] = chars[rand()%chars.length()];
    }
    return s;
}

