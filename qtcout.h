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
    const QtCout & operator <<(double d) const {
       // qDebug()<<s;
        cout <<d;
        return *this;
    }
    const QtCout & operator <<(char c) const {
       // qDebug()<<s;
        cout <<c;
        return *this;
    }
};

#endif // QTCOUT_H
