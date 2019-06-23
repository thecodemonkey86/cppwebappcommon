#include "uploadedfilestringkeyarray.h"

UploadedFileStringKeyArray::UploadedFileStringKeyArray(const QString & fieldName) : AbstractUploadedFile (fieldName)
{

}

UploadedFileStringKeyArray::UploadedFileStringKeyArray(const QString &fieldName, const QString &key, const UploadedFile &file) : AbstractUploadedFile (fieldName)
{
    insert(key,file);
}


void UploadedFileStringKeyArray::cleanup() const
{
    for(const auto & k:keys()){
        (*this)[k].cleanup();
    }
}
