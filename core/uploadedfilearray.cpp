#include "uploadedfilearray.h"


UploadedFileArray::UploadedFileArray() : AbstractUploadedFile()
{

}

UploadedFileArray::UploadedFileArray(const QString &fieldName) : AbstractUploadedFile (fieldName)
{

}

UploadedFileArray::UploadedFileArray(const QString &fieldName, const UploadedFile &first)  : AbstractUploadedFile (fieldName)
{
    append(first);
}

UploadedFileArray::~UploadedFileArray()
{

}

bool UploadedFileArray::operator ==(const UploadedFileArray &other) const
{
    return this->getFieldName() == other.getFieldName();
}


size_t qHash(const UploadedFileArray & u)
{
 return qHash(u.getFieldName());
}


void UploadedFileArray::cleanup() const
{
    for(const auto & u : *this)
    {
        u.cleanup();
    }
}
