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
    UploadedFileStringKeyArray(const QString & fieldName,const QString & key,const UploadedFile & file);
    virtual ~UploadedFileStringKeyArray() = default;

    // AbstractUploadedFile interface
public:
    virtual void cleanup() const override;
};

#endif // UPLOADEDFILESTRINGKEYARRAY_H
