#ifndef UPLOADEDFILESTRINGKEYARRAY_H
#define UPLOADEDFILESTRINGKEYARRAY_H
#include "abstractuploadedfile.h"
#include "uploadedfile.h"
#include <QHash>

class UploadedFileStringKeyArray : public AbstractUploadedFile, public QHash<QString, UploadedFile>
{
public:
    UploadedFileStringKeyArray(const QString & fieldName);
    virtual ~UploadedFileStringKeyArray() = default;
};

#endif // UPLOADEDFILESTRINGKEYARRAY_H
