#include "fastcgioutput.h"
#include "fcgiapp.h"

#include <QIODevice>

void FastCgiOutput::write(QStringView s, FCGX_Stream *out) {
  auto data = s.toUtf8();
  FCGX_PutStr(data.constData(),data.size(),out);
}

void FastCgiOutput::write(QLatin1StringView s, FCGX_Stream *out) {
  FCGX_PutStr(s.constData(),s.size(),out);
}


void FastCgiOutput::write(const QByteArray &b, FCGX_Stream *out) {
  FCGX_PutStr(b.constData(),b.size(),out);
}

void FastCgiOutput::write(QIODevice & ioDevice, FCGX_Stream *out)
{
  if(ioDevice.open(QIODevice::ReadOnly))
  {
      char buf[8192];
      qint64 r=-1;
      while( (r=ioDevice.read(buf, sizeof(buf)))>0) {
          FCGX_PutStr(buf,r,out);
      }
  }
}

void FastCgiOutput::write(int d, FCGX_Stream *out) {
  write(QByteArray::number(d),out);
}



void FastCgiOutput::write(unsigned int d, FCGX_Stream *out) {
  write(QByteArray::number(d),out);
}



void FastCgiOutput::write(unsigned long long d, FCGX_Stream *out) {
  write(QByteArray::number(d),out);
}



void FastCgiOutput::write(bool b, FCGX_Stream *out) {
  write(b ? "1" : "0",out);
}



void FastCgiOutput::write(long long number, FCGX_Stream *out) {
  write(QByteArray::number(number),out);
}



void FastCgiOutput::write(long number, FCGX_Stream *out) {
  write(QByteArray::number(static_cast<int64_t>(number)),out);

}



void FastCgiOutput::write(double number, FCGX_Stream *out) {
  write(QByteArray::number(number),out);

}



void FastCgiOutput::write(char c, FCGX_Stream *out) {
  FCGX_PutChar(c,out);
}



void FastCgiOutput::write(const char *c, FCGX_Stream *out) {
  FCGX_PutStr(c, static_cast<int>(strnlen(c,INT32_MAX)),out) ;
}



void FastCgiOutput::write(const char *c, int len, FCGX_Stream *out) {
  FCGX_PutStr(c, len,out) ;
}



void FastCgiOutput::writeToBuffer(QStringView s, QString &buffer) {
  buffer +=s;
}



void FastCgiOutput::writeToBuffer(const QByteArray &b, QString &buffer) {
  buffer += QString::fromUtf8(b);
}



void FastCgiOutput::writeToBuffer(int d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeToBuffer(double d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeToBuffer(unsigned int d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeToBuffer(unsigned long long d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeToBuffer(bool b, QString &buffer) {
  buffer +=  b ? QChar('1') : QChar('0');
}



void FastCgiOutput::writeToBuffer(long long number, QString &buffer) {
  buffer += QString::number(number);
}



void FastCgiOutput::writeToBuffer(long number, QString &buffer) {
  buffer += QString::number(number);

}



void FastCgiOutput::writeToBuffer(char c, QString &buffer) {
  buffer += c;
}



void FastCgiOutput::writeToBuffer(const char *c, QString &buffer) {
  buffer += c ;
}



void FastCgiOutput::writeHtmlEncoded(const QString &s, FCGX_Stream *out) {
  auto data = s.toHtmlEscaped().toUtf8();
  FCGX_PutStr(data.constData(),data.size(),out);
}



void FastCgiOutput::writeHtmlDoubleEncoded(const QString &s, FCGX_Stream *out) {
  auto data = s.toHtmlEscaped().toHtmlEscaped().toUtf8();
  FCGX_PutStr(data.constData(),data.size(),out);
}



void FastCgiOutput::writeHtmlEncoded(const QByteArray &b, FCGX_Stream *out) {
  write(QString::fromUtf8(b).toHtmlEscaped(),out);
}



void FastCgiOutput::writeHtmlDoubleEncoded(const QByteArray &b, FCGX_Stream *out) {
  write(QString::fromUtf8(b).toHtmlEscaped().toHtmlEscaped(),out);
}



void FastCgiOutput::writeHtmlDoubleEncoded(const char *s, FCGX_Stream *out) {
  write(QString::fromUtf8(s).toHtmlEscaped().toHtmlEscaped(),out);
}



void FastCgiOutput::writeHtmlDoubleEncoded(int64_t i, FCGX_Stream *out) {
  write(QByteArray::number(i),out);
}

void FastCgiOutput::writeHtmlDoubleEncoded(int i, FCGX_Stream *out) {
  write(QByteArray::number(i),out);
}


void FastCgiOutput::writeHtmlDoubleEncoded(double d, FCGX_Stream *out) {
  write(QByteArray::number(d),out);
}

void FastCgiOutput::writeHtmlEncoded(int d, FCGX_Stream *out) {
  write(d,out);
}



void FastCgiOutput::writeHtmlEncoded(unsigned int d, FCGX_Stream *out) {
  write(d,out);
}



void FastCgiOutput::writeHtmlEncoded(unsigned long long d, FCGX_Stream *out) {
  write(d,out);
}



void FastCgiOutput::writeHtmlEncoded(bool b, FCGX_Stream *out) {
  write(b ? "1" : "0",out);
}



void FastCgiOutput::writeHtmlEncoded(long long number, FCGX_Stream *out) {
  write(number, out);
}



void FastCgiOutput::writeHtmlEncoded(long number, FCGX_Stream *out) {
  write(number, out);

}



void FastCgiOutput::writeHtmlEncoded(double number, FCGX_Stream *out) {
  write(number, out);

}



void FastCgiOutput::writeHtmlEncoded(char c, FCGX_Stream *out) {
  writeHtmlEncoded(QString(QChar(c)),out);
}



void FastCgiOutput::writeHtmlEncoded(const char *c, FCGX_Stream *out) {
  writeHtmlEncoded(QString::fromUtf8(c),out);
}



void FastCgiOutput::writeHtmlEncodedToBuffer(const QString &s, QString &buffer) {
  buffer +=s.toHtmlEscaped();
}



void FastCgiOutput::writeHtmlEncodedToBuffer(const QByteArray &b, QString &buffer) {
  buffer += QString::fromUtf8(b).toHtmlEscaped();
}



void FastCgiOutput::writeHtmlEncodedToBuffer(int d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeHtmlEncodedToBuffer(double d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeHtmlEncodedToBuffer(unsigned int d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeHtmlEncodedToBuffer(unsigned long long d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeHtmlEncodedToBuffer(bool b, QString &buffer) {
  buffer +=  b ? QChar('1') : QChar('0');
}



void FastCgiOutput::writeHtmlEncodedToBuffer(long long number, QString &buffer) {
  buffer += QString::number(number);
}



void FastCgiOutput::writeHtmlEncodedToBuffer(long number, QString &buffer) {
  buffer += QString::number(number);
}



void FastCgiOutput::writeHtmlEncodedToBuffer(char c, QString &buffer) {
  buffer += QString(QChar(c)).toHtmlEscaped();
}



void FastCgiOutput::writeHtmlEncodedToBuffer(const char *c, QString &buffer) {
  buffer += QString::fromUtf8(c).toHtmlEscaped() ;
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(const QString &s, QString &buffer) {
  buffer +=s.toHtmlEscaped().toHtmlEscaped();
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(const QByteArray &b, QString &buffer) {
  buffer += QString::fromUtf8(b).toHtmlEscaped().toHtmlEscaped();
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(int d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(unsigned int d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(unsigned long long d, QString &buffer) {
  buffer += QString::number(d);
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(bool b, QString &buffer) {
  buffer +=  b ? QChar('1') : QChar('0');
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(long long number, QString &buffer) {
  buffer += QString::number(number);
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(long number, QString &buffer) {
  buffer += QString::number(number);
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(double number, QString &buffer) {
  buffer += QString::number(number);
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(char c, QString &buffer) {
  buffer += QString(QChar(c)).toHtmlEscaped().toHtmlEscaped();
}



void FastCgiOutput::writeHtmlDoubleEncodedToBuffer(const char *c, QString &buffer) {
  buffer += QString::fromUtf8(c).toHtmlEscaped().toHtmlEscaped() ;
}


