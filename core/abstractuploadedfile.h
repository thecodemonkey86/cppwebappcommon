#ifndef ABSTRACTUPLOADEDFILE_H
#define ABSTRACTUPLOADEDFILE_H
#include <QString>

class AbstractUploadedFile
{
private:
     QString fieldName;
public:
    AbstractUploadedFile(const QString & fieldName);
    virtual ~AbstractUploadedFile() = default;

    QString getFieldName() const;
};

#endif // ABSTRACTUPLOADEDFILE_H
