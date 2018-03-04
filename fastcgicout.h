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
private:
    FastCgiCout() {

    }

public:
    inline static void write(const QString&s) {
        auto data = s.toUtf8();
        cout.write(data.data(),data.length());
    }
    inline static void write(const QByteArray&b) {
        cout.write(b.data(),b.length());
    }
    inline static void write(double d) {
        cout <<d;
    }
    inline static void write(int d) {
        cout <<d;
    }
    inline static void write(long long number) {
        cout <<number;
    }
    inline static void write(long number) {
        cout <<number;

    }
    inline static void write(char c) {
        cout <<c;
    }

    inline static void write(const char* c) {
        cout.write(c, strnlen(c,INT32_MAX));
    }
};

#endif // FASTCGICOUT_H

