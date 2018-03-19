#ifndef ABSTRACTUPLOADEDFILE_H
#define ABSTRACTUPLOADEDFILE_H
#include <QString>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT AbstractUploadedFile
{
private:
     QString fieldName;
public:
    AbstractUploadedFile(const QString & fieldName);
    virtual ~AbstractUploadedFile() = default;

    QString getFieldName() const;
};

#endif // ABSTRACTUPLOADEDFILE_H
