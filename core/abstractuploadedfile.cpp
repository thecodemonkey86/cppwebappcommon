#include "abstractuploadedfile.h"


QString AbstractUploadedFile::getFieldName() const
{
    return fieldName;
}

bool AbstractUploadedFile::operator ==(const AbstractUploadedFile &other) const
{
    return fieldName == other.fieldName;
}

AbstractUploadedFile::AbstractUploadedFile()
{

}

AbstractUploadedFile::AbstractUploadedFile(const QString & fieldName)
{
    this->fieldName = fieldName;
}

