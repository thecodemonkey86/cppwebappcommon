#pragma once

#include <QPair>
#include <QString>
#include "webappcommon_global.h"
#include "abstractuploadedfile.h"

/**
 * @brief provides access to uploaded files in the system temp directory
 */
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
    virtual ~UploadedFile() override = default;

    /**
     * @brief get the fize size (bytes)
     * @return
     */
    int64_t getSize() const;

    /**
     * @brief get the full file path (system temp directory)
     * @return
     */
    QString getTemporaryPath() const;

    /**
     * @brief method to move a file to the provided destination directory
     * @param path
     * @return
     */
    bool move(const QString & path);

    /**
     * @brief get the MIME type
     * @return
     */
    QString getMimeType() const;

    bool operator ==(const UploadedFile & other) const;

    /**
     * @brief gets the file name provided in the original request
     * @return
     */
    QString getSourceFileName() const;

    /**
     * @brief readAllBytes
     * @return
     */
    QByteArray readAllBytes() const;

    /**
     * @brief if the file is discarded for some reason, i.e. has not been moved to a destination folder, this method deletes the temp file. This method is called and cascaded in RequestData's destructor
     */
    virtual void cleanup() const override;
};
size_t qHash(const UploadedFile & u);
