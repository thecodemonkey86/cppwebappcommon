#include "uploadedfile.h"
#include <QFileInfo>

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


UploadedFile::UploadedFile()  : AbstractUploadedFile(QString())
{

}

UploadedFile::UploadedFile(const QString & sourceFileName, const QString & fieldName,const QString &temporaryPath, const QString &mimeType,int64_t size)
    : AbstractUploadedFile (fieldName)
{
    this->temporaryPath = temporaryPath;
    this->mimeType = mimeType;
    this->size = size;
    this->sourceFileName = sourceFileName;
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




uint qHash(const UploadedFile &u)
{
    return qHash(u.getFieldName());
}

