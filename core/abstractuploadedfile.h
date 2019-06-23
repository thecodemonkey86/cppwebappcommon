#ifndef ABSTRACTUPLOADEDFILE_H
#define ABSTRACTUPLOADEDFILE_H
#include <QString>
#include "webappcommon_global.h"
class WEBAPPCOMMONSHARED_EXPORT AbstractUploadedFile
{
private:
     QString fieldName;
public:
     AbstractUploadedFile();
    AbstractUploadedFile(const QString & fieldName);
    virtual ~AbstractUploadedFile() = default;

    QString getFieldName() const;
      bool operator ==(const AbstractUploadedFile & other) const;
       virtual void cleanup() const =0;
};

#endif // ABSTRACTUPLOADEDFILE_H
