#ifndef FASTCGIOUTPUT_H
#define FASTCGIOUTPUT_H
#include <QString>
#include "fcgio.h"
class FastCgiOutput
{
public:
    FastCgiOutput();
    inline static void write(const QString&s, FCGX_Stream *out) {
        auto data = s.toUtf8();
       FCGX_PutStr(data.data(),data.length(),out);
    }
    inline static void write(const QByteArray&b, FCGX_Stream *out) {
        FCGX_PutStr(b.data(),b.length(),out);
    }

    inline static void write(int d, FCGX_Stream *out) {
         write(QString::number(d),out);
    }

    inline static void write(unsigned int d, FCGX_Stream *out) {
        write(QString::number(d),out);
    }

    inline static void write(unsigned long long d, FCGX_Stream *out) {
       write(QString::number(d),out);
    }

    inline static void write(bool b, FCGX_Stream *out) {
        write(b ? "1" : "0",out);
    }

    inline static void write(long long number, FCGX_Stream *out) {
        write(QString::number(number),out);
    }
    inline static void write(long number, FCGX_Stream *out) {
       write(QString::number(number),out);

    }
    inline static void write(char c, FCGX_Stream *out) {
        FCGX_PutChar(c,out);
    }

    inline static void write(const char* c, FCGX_Stream *out) {
        FCGX_PutStr(c, static_cast<int>(strnlen(c,INT32_MAX)),out) ;
    }
};

#endif // FASTCGIOUTPUT_H
