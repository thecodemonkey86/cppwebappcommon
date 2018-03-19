#include "uploadedfile.h"
#include <QFileInfo>

QString UploadedFile::getMimeType() const
{
    return mimeType;
}

UploadedFile::UploadedFile(const QString & fieldName,const QString &temporaryPath, const QString &mimeType,int64_t size)
    : AbstractUploadedFile (fieldName)
{
    this->temporaryPath = temporaryPath;
    this->mimeType = mimeType;
    this->size = size;
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
    return file.rename(path);
}



