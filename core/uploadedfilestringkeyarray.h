#ifndef UPLOADEDFILESTRINGKEYARRAY_H
#define UPLOADEDFILESTRINGKEYARRAY_H
#include "abstractuploadedfile.h"
#include "uploadedfile.h"
#include <QHash>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT UploadedFileStringKeyArray : public AbstractUploadedFile, public QHash<QString, UploadedFile>
{
public:
    UploadedFileStringKeyArray(const QString & fieldName);
    virtual ~UploadedFileStringKeyArray() = default;
};

#endif // UPLOADEDFILESTRINGKEYARRAY_H
