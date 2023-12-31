#pragma once


#include "abstractuploadedfile.h"
#include "uploadedfile.h"
#include <QVector>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT UploadedFileArray : public AbstractUploadedFile, public QVector<UploadedFile>
{
public:
    UploadedFileArray();
    UploadedFileArray(const QString & fieldName);
    UploadedFileArray(const QString & fieldName, const UploadedFile & first);
    virtual ~UploadedFileArray();
    bool operator == (const UploadedFileArray & other) const;

    // AbstractUploadedFile interface
public:
    virtual void cleanup() const override;
};

size_t qHash(const UploadedFileArray &);

