#ifndef POSTDATA_H
#define POSTDATA_H

#include <QString>

class PostData
{
public:
    PostData();
    static QString string(const QString&name);
    static int integer(const QString&name);
    static double dbl(const QString&name);
};

#endif // POSTDATA_H
