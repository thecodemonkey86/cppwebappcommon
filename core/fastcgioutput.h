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

    /**
        * @brief writes a QString as UTF-8 to a string buffer
        * @param s
        * @param out
        */
       inline static void writeToBuffer(const QString&s, QString & buffer) {
          buffer +=s;
       }

       /**
        * @brief writes a QByteArray to a string buffer
        * @param b
        * @param out
        */
       inline static void writeToBuffer(const QByteArray&b, QString & buffer) {
           buffer += QString::fromUtf8(b);
       }

       /**
        * @brief writes a string representation of an integer to a string buffer
        * @param d
        * @param out
        */
       inline static void writeToBuffer(int d, QString & buffer) {
            buffer += QString::number(d);
       }

       /**
        * @brief writes a string representation of an unsigned integer to a string buffer
        * @param d
        * @param out
        */
       inline static void writeToBuffer(unsigned int d, QString & buffer) {
          buffer += QString::number(d);
       }

       /**
        * @brief writes a string representation of an unsigned 64 bit integer to a string buffer
        * @param d
        * @param out
        */
       inline static void writeToBuffer(unsigned long long d, QString & buffer) {
          buffer += QString::number(d);
       }

       /**
        * @brief writes a string representation of a boolean value ("1" or "0") to a string buffer
        * @param d
        * @param out
        */
       inline static void writeToBuffer(bool b, QString & buffer) {
          buffer +=  b ? QChar('1') : QChar('0');
       }


       /**
        * @brief writes a string representation of a 64 bit integer to a string buffer
        * @param number
        * @param out
        */
       inline static void writeToBuffer(long long number, QString & buffer) {
           buffer += QString::number(number);
       }

       /**
        * @brief writes a string representation of a long integer to a string buffer
        * @param number
        * @param out
        */
       inline static void writeToBuffer(long number, QString & buffer) {
          buffer += QString::number(number);

       }

       /**
        * @brief writes a single character to a string buffer
        * @param number
        * @param out
        */
       inline static void writeToBuffer(char c, QString & buffer) {
           buffer += c;
       }

       /**
        * @brief writes a C-String to a string buffer
        * @param number
        * @param out
        */
       inline static void writeToBuffer(const char* c, QString & buffer) {
           buffer += c ;
       }

       /**
          * @brief writes a QString as UTF-8 to the FastCGI output stream
          * @param s
          * @param out
          */
         inline static void writeHtmlEncoded(const QString&s, FCGX_Stream *out) {
             auto data = s.toHtmlEscaped().toUtf8();
            FCGX_PutStr(data.data(),data.length(),out);
         }

         /**
          * @brief writes a QString as UTF-8 to the FastCGI output stream
          * @param s
          * @param out
          */
         inline static void writeHtmlDoubleEncoded(const QString&s, FCGX_Stream *out) {
           auto data = s.toHtmlEscaped().toHtmlEscaped().toUtf8();
           FCGX_PutStr(data.data(),data.length(),out);
         }

         /**
          * @brief writes a QByteArray to the FastCGI output stream
          * @param b
          * @param out
          */
         inline static void writeHtmlEncoded(const QByteArray&b, FCGX_Stream *out) {
             write(QString::fromUtf8(b).toHtmlEscaped(),out);
         }
         /**
          * @brief writes a QByteArray to the FastCGI output stream
          * @param b
          * @param out
          */
         inline static void writeHtmlDoubleEncoded(const QByteArray&b, FCGX_Stream *out) {
           write(QString::fromUtf8(b).toHtmlEscaped().toHtmlEscaped(),out);
         }
         /**
          * @brief writes a string representation of an integer to the FastCGI output stream
          * @param d
          * @param out
          */
         inline static void writeHtmlEncoded(int d, FCGX_Stream *out) {
              write(d,out);
         }

         /**
          * @brief writes a string representation of an unsigned integer to the FastCGI output stream
          * @param d
          * @param out
          */
         inline static void writeHtmlEncoded(unsigned int d, FCGX_Stream *out) {
             write(d,out);
         }

         /**
          * @brief writes a string representation of an unsigned 64 bit integer to the FastCGI output stream
          * @param d
          * @param out
          */
         inline static void writeHtmlEncoded(unsigned long long d, FCGX_Stream *out) {
            write(d,out);
         }

         /**
          * @brief writes a string representation of a boolean value ("1" or "0") to the FastCGI output stream
          * @param d
          * @param out
          */
         inline static void writeHtmlEncoded(bool b, FCGX_Stream *out) {
             write(b ? "1" : "0",out);
         }


         /**
          * @brief writes a string representation of a 64 bit integer to the FastCGI output stream
          * @param number
          * @param out
          */
         inline static void writeHtmlEncoded(long long number, FCGX_Stream *out) {
             write(number, out);
         }

         /**
          * @brief writes a string representation of a long integer to the FastCGI output stream
          * @param number
          * @param out
          */
         inline static void writeHtmlEncoded(long number, FCGX_Stream *out) {
            write(number, out);

         }

         /**
          * @brief writes a single character to the FastCGI output stream
          * @param number
          * @param out
          */
         inline static void writeHtmlEncoded(char c, FCGX_Stream *out) {
             writeHtmlEncoded(QString(QChar(c)),out);
         }

         /**
          * @brief writes a C-String to the FastCGI output stream
          * @param number
          * @param out
          */
         inline static void writeHtmlEncoded(const char* c, FCGX_Stream *out) {
             writeHtmlEncoded(QString::fromUtf8(c),out);
         }

          /**
            * @brief writes a QString as UTF-8 to a string buffer
            * @param s
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(const QString&s, QString & buffer) {
              buffer +=s.toHtmlEscaped();
           }

           /**
            * @brief writes a QByteArray to a string buffer
            * @param b
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(const QByteArray&b, QString & buffer) {
               buffer += QString::fromUtf8(b).toHtmlEscaped();
           }

           /**
            * @brief writes a string representation of an integer to a string buffer
            * @param d
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(int d, QString & buffer) {
                buffer += QString::number(d);
           }

           /**
            * @brief writes a string representation of an unsigned integer to a string buffer
            * @param d
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(unsigned int d, QString & buffer) {
               buffer += QString::number(d);
           }

           /**
            * @brief writes a string representation of an unsigned 64 bit integer to a string buffer
            * @param d
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(unsigned long long d, QString & buffer) {
              buffer += QString::number(d);
           }

           /**
            * @brief writes a string representation of a boolean value ("1" or "0") to a string buffer
            * @param d
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(bool b, QString & buffer) {
              buffer +=  b ? QChar('1') : QChar('0');
           }


           /**
            * @brief writes a string representation of a 64 bit integer to a string buffer
            * @param number
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(long long number, QString & buffer) {
              buffer += QString::number(number);
           }

           /**
            * @brief writes a string representation of a long integer to a string buffer
            * @param number
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(long number, QString & buffer) {
               buffer += QString::number(number);
           }

           /**
            * @brief writes a single character to a string buffer
            * @param number
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(char c, QString & buffer) {
               buffer += QString(QChar(c)).toHtmlEscaped();
           }

           /**
            * @brief writes a C-String to a string buffer
            * @param number
            * @param out
            */
           inline static void writeHtmlEncodedToBuffer(const char* c, QString & buffer) {
               buffer += QString::fromUtf8(c).toHtmlEscaped() ;
           }


           /**
            * @brief writes a QString as UTF-8 to a string buffer
            * @param s
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(const QString&s, QString & buffer) {
             buffer +=s.toHtmlEscaped().toHtmlEscaped();
           }

           /**
            * @brief writes a QByteArray to a string buffer
            * @param b
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(const QByteArray&b, QString & buffer) {
             buffer += QString::fromUtf8(b).toHtmlEscaped().toHtmlEscaped();
           }

           /**
            * @brief writes a string representation of an integer to a string buffer
            * @param d
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(int d, QString & buffer) {
             buffer += QString::number(d);
           }

           /**
            * @brief writes a string representation of an unsigned integer to a string buffer
            * @param d
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(unsigned int d, QString & buffer) {
             buffer += QString::number(d);
           }

           /**
            * @brief writes a string representation of an unsigned 64 bit integer to a string buffer
            * @param d
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(unsigned long long d, QString & buffer) {
             buffer += QString::number(d);
           }

           /**
            * @brief writes a string representation of a boolean value ("1" or "0") to a string buffer
            * @param d
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(bool b, QString & buffer) {
             buffer +=  b ? QChar('1') : QChar('0');
           }


           /**
            * @brief writes a string representation of a 64 bit integer to a string buffer
            * @param number
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(long long number, QString & buffer) {
             buffer += QString::number(number);
           }

           /**
            * @brief writes a string representation of a long integer to a string buffer
            * @param number
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(long number, QString & buffer) {
             buffer += QString::number(number);
           }

           /**
            * @brief writes a single character to a string buffer
            * @param number
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(char c, QString & buffer) {
             buffer += QString(QChar(c)).toHtmlEscaped().toHtmlEscaped();
           }

           /**
            * @brief writes a C-String to a string buffer
            * @param number
            * @param out
            */
           inline static void writeHtmlDoubleEncodedToBuffer(const char* c, QString & buffer) {
             buffer += QString::fromUtf8(c).toHtmlEscaped().toHtmlEscaped() ;
           }
};

#endif // FASTCGIOUTPUT_H
