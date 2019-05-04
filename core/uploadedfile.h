#ifndef UPLOADEDFILE_H
#define UPLOADEDFILE_H
#include <QPair>
#include <QString>
#include "webappcommon_global.h"
#include "abstractuploadedfile.h"
class WEBAPPCOMMONSHARED_EXPORT UploadedFile : public AbstractUploadedFile
{
private:

    QString temporaryPath;
    QString sourceFileName;
    QString mimeType;
    int64_t size;
public:
    UploadedFile();
    UploadedFile(const QString & sourceFileName,const QString & fieldName, const QString & temporaryPath,const QString & mimeType,int64_t size);
    virtual ~UploadedFile() = default;
    int64_t getSize() const;
    QString getTemporaryPath() const;
    bool move(const QString & path);
    QString getMimeType() const;

    bool operator ==(const UploadedFile & other) const;
    QString getSourceFileName() const;
};
uint qHash(const UploadedFile & u);
#endif // UPLOADEDFILE_H
