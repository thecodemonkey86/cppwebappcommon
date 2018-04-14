#include "uploadedfilearray.h"


UploadedFileArray::UploadedFileArray() : AbstractUploadedFile()
{

}

UploadedFileArray::UploadedFileArray(const QString &fieldName) : AbstractUploadedFile (fieldName)
{

}

UploadedFileArray::~UploadedFileArray()
{

}

bool UploadedFileArray::operator ==(const UploadedFileArray &other) const
{
    return this->getFieldName() == other.getFieldName();
}


uint qHash(const UploadedFileArray & u)
{
 return qHash(u.getFieldName());
}
