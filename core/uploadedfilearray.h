#ifndef UPLOADEDFILEARRAY_H
#define UPLOADEDFILEARRAY_H

#include "abstractuploadedfile.h"
#include "uploadedfile.h"
#include <QList>
#include <QVariant>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT UploadedFileArray : public AbstractUploadedFile, public QList<UploadedFile>
{
public:
    UploadedFileArray();
    UploadedFileArray(const QString & fieldName);
    virtual ~UploadedFileArray();
    bool operator == (const UploadedFileArray & other) const;
};

uint qHash(const UploadedFileArray &);

#endif // UPLOADEDFILEARRAY_H
