#ifndef QTCOUT_H
#define QTCOUT_H

#include <iostream>
#include <QString>
#include <QDebug>
#include "webappcommon_global.h"
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT QtCout
{
public:
    QtCout();
    const QtCout & operator <<(const QString&s) const {
       // qDebug()<<s;
        cout << s.toUtf8().data();
        return *this;
    }
};

#endif // QTCOUT_H
