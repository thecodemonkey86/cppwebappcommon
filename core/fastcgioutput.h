#ifndef FASTCGIOUTPUT_H
#define FASTCGIOUTPUT_H
#include <QString>
#include "fcgio.h"
class FastCgiOutput
{
public:
    FastCgiOutput();

    /**
     * @brief writes a QString as UTF-8 to the FastCGI output stream
     * @param s
     * @param out
     */
    inline static void write(const QString&s, FCGX_Stream *out) {
        auto data = s.toUtf8();
       FCGX_PutStr(data.data(),data.length(),out);
    }

    /**
     * @brief writes a QByteArray to the FastCGI output stream
     * @param b
     * @param out
     */
    inline static void write(const QByteArray&b, FCGX_Stream *out) {
        FCGX_PutStr(b.data(),b.length(),out);
    }

    /**
     * @brief writes a string representation of an integer to the FastCGI output stream
     * @param d
     * @param out
     */
    inline static void write(int d, FCGX_Stream *out) {
         write(QString::number(d),out);
    }

    /**
     * @brief writes a string representation of an unsigned integer to the FastCGI output stream
     * @param d
     * @param out
     */
    inline static void write(unsigned int d, FCGX_Stream *out) {
        write(QString::number(d),out);
    }

    /**
     * @brief writes a string representation of an unsigned 64 bit integer to the FastCGI output stream
     * @param d
     * @param out
     */
    inline static void write(unsigned long long d, FCGX_Stream *out) {
       write(QString::number(d),out);
    }

    /**
     * @brief writes a string representation of a boolean value ("1" or "0") to the FastCGI output stream
     * @param d
     * @param out
     */
    inline static void write(bool b, FCGX_Stream *out) {
        write(b ? "1" : "0",out);
    }


    /**
     * @brief writes a string representation of a 64 bit integer to the FastCGI output stream
     * @param number
     * @param out
     */
    inline static void write(long long number, FCGX_Stream *out) {
        write(QString::number(number),out);
    }

    /**
     * @brief writes a string representation of a long integer to the FastCGI output stream
     * @param number
     * @param out
     */
    inline static void write(long number, FCGX_Stream *out) {
       write(QString::number(number),out);

    }

    /**
     * @brief writes a single character to the FastCGI output stream
     * @param number
     * @param out
     */
    inline static void write(char c, FCGX_Stream *out) {
        FCGX_PutChar(c,out);
    }

    /**
     * @brief writes a C-String to the FastCGI output stream
     * @param number
     * @param out
     */
    inline static void write(const char* c, FCGX_Stream *out) {
        FCGX_PutStr(c, static_cast<int>(strnlen(c,INT32_MAX)),out) ;
    }
};

#endif // FASTCGIOUTPUT_H
