#ifndef REQUESTDATA_H
#define REQUESTDATA_H

#include <QString>
#include <QFile>
#include <QHash>
#include <QVector>
#include "core/requestparam.h"
#include "abstractuploadedfile.h"
#include "uploadedfile.h"
#include "uploadedfilearray.h"
#include "uploadedfilestringkeyarray.h"
#include "arrayrequestparam.h"
#include "abstractstringkeyarrayparam.h"
#include "fcgio.h"
#include <QUrl>
#include <memory>

using namespace std;

class WEBAPPCOMMONSHARED_EXPORT RequestData
{
private:
    static constexpr char CR = '\r';
    static constexpr char NL = '\n';
    static constexpr int BUF_SIZE = 8192;

    QHash<QString, AbstractRequestParam*> getParams;
    QHash<QString, AbstractRequestParam*> postParams;
    QVector<shared_ptr<AbstractUploadedFile>> uploadFiles;

    void parseParams(const QString&requestString, QHash<QString, AbstractRequestParam*>& params);
    void parseGetParams(const QUrl& url);
    void parsePostParams(const FCGX_Request & request);

    inline void parseParam(const QString & fieldName, const QString &value, QHash<QString, AbstractRequestParam*>& params);
    inline static void writeFileBuf(QFile * file, int & pos, char* & buf, char c );

public:
 RequestData(const FCGX_Request & request, const QUrl &url);
    ~RequestData();
    const QString & getString(const QString&name) const;
    const QString & postString(const QString&name) const;
    int getInt(const QString&name) const;
    int postInt(const QString&name) const;
    double postDouble(const QString&name) const;
    double getDouble(const QString&name) const;
    bool postBool(const QString&name) const;
    ArrayRequestParam * getArray(const QString&name) const;
    QString getArrayValueString(const QString &name, const QString &key) const;
    QString getArrayValueString(const QString &name, int index) const;
    int getArrayValueInt(const QString &name, const QString &key) const;
    int getArrayValueInt(const QString &name, int index) const;
    bool isGetParamSet(const QString&name) const;
    bool isPostParamSet(const QString&name) const;
    QStringList postFieldNames() const;
    shared_ptr<UploadedFile> uploadedFile(const QString&fieldname) const;
    shared_ptr<UploadedFileArray> uploadedFileArray(const QString&fieldname) const;
    shared_ptr<UploadedFileStringKeyArray> uploadedFileArrayStringKey(const QString&fieldname) const;

};

#endif // REQUESTDATA_H
