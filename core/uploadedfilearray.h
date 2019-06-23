#ifndef UPLOADEDFILEARRAY_H
#define UPLOADEDFILEARRAY_H

#include "abstractuploadedfile.h"
#include "uploadedfile.h"
#include <QVector>
#include <QVariant>
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

uint qHash(const UploadedFileArray &);

#endif // UPLOADEDFILEARRAY_H
