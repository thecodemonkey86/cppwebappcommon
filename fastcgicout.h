#ifndef FASTCGICOUT_H
#define FASTCGICOUT_H

#include <iostream>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include "webappcommon_global.h"
using namespace std;


class WEBAPPCOMMONSHARED_EXPORT FastCgiCout
{
public:
    FastCgiCout() {

    }

    const inline FastCgiCout & operator <<(const QString&s) const {
       // qDebug()<<s;
        auto data = s.toUtf8();
        cout.write(data.data(),data.length());
        return *this;
    }
    const inline FastCgiCout & operator <<(const QByteArray&b) const {
       // qDebug()<<s;
        cout.write(b.data(),b.length());
        return *this;
    }
    const inline FastCgiCout & operator <<(double d) const {
       // qDebug()<<s;
        cout <<d;
        return *this;
    }
    const inline FastCgiCout & operator <<(char c) const {
       // qDebug()<<s;
        cout <<c;
        return *this;
    }

    const inline FastCgiCout & operator <<(const char* c) const {
       // qDebug()<<s;
        cout.write(c, strnlen(c,INT32_MIN));
//        cout << c;
        return *this;
    }
};

#endif // FASTCGICOUT_H

