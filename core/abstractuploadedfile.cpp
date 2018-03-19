#include "abstractuploadedfile.h"


QString AbstractUploadedFile::getFieldName() const
{
    return fieldName;
}

AbstractUploadedFile::AbstractUploadedFile(const QString & fieldName)
{
    this->fieldName = fieldName;
}

