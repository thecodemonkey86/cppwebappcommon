#ifndef UPLOADEDFILEARRAY_H
#define UPLOADEDFILEARRAY_H

#include "abstractuploadedfile.h"
#include "uploadedfile.h"
#include <QList>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT UploadedFileArray : public AbstractUploadedFile, public QList<UploadedFile>
{
public:
    UploadedFileArray(const QString & fieldName);
    virtual ~UploadedFileArray() = default;
};

#endif // UPLOADEDFILEARRAY_H
