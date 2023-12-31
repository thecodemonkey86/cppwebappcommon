#include "uploadedfile.h"
#include <QFileInfo>
#include "exception/qtexception.h"

QString UploadedFile::getMimeType() const
{
    return mimeType;
}

bool UploadedFile::operator ==(const UploadedFile &other) const
{
    return other.temporaryPath == this->temporaryPath;
}

QString UploadedFile::getSourceFileName() const
{
  return sourceFileName;
}

QByteArray UploadedFile::readAllBytes() const
{
  QFile f(temporaryPath);

  if(f.exists() && f.open(QIODevice::ReadOnly)) {
    return f.readAll();
  }
  throwExceptionWithLine(f.errorString());
}

void UploadedFile::cleanup() const
{
    QFile f(temporaryPath);

    if(f.exists()) {
        f.remove();
    }
}


UploadedFile::UploadedFile()  : AbstractUploadedFile(QString()),size(0LL)
{

}

UploadedFile::UploadedFile(const QString & sourceFileName, const QString & fieldName,const QString &temporaryPath, const QString &mimeType,int64_t size)
    : AbstractUploadedFile (fieldName) ,
    temporaryPath(temporaryPath),
    mimeType(mimeType),
    size(size),
    sourceFileName(sourceFileName)
{

}


int64_t UploadedFile::getSize() const
{
    return  this->size;
}


QString UploadedFile::getTemporaryPath() const
{
    return temporaryPath;
}

bool UploadedFile::move(const QString &path)
{
    QFile file(temporaryPath);
    QFile dest(path);
    if(dest.exists()) {
        dest.remove();
    }
    return file.rename(path);
}




size_t qHash(const UploadedFile &u)
{
    return qHash(u.getFieldName());
}

