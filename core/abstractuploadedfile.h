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

      /**
     * @brief if the file is discarded for some reason, i.e. has not been moved to a destination folder, this method deletes the temp file. This method is called and cascaded in RequestData's destructor
     */
       virtual void cleanup() const =0;
};

#endif // ABSTRACTUPLOADEDFILE_H
