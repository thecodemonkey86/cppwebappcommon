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
#include "stringkeyarrayparam.h"
#include <QUrl>
#include <memory>
#include "webappcommon_global.h"
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT RequestData
{
private:
    static constexpr char CR = '\r';
    static constexpr char NL = '\n';
    static constexpr char HYPHEN = '-';
    static constexpr int BUF_SIZE = 8192;

    QHash<QString, AbstractRequestParam*> getParams;
    QHash<QString, AbstractRequestParam*> postParams;
    QVector<AbstractUploadedFile*> uploadFiles;

    void parseGetParams(const QUrl& url);
    void parsePostParams(const FCGX_Request & request);

    inline void addToHashtable(const QString & fieldName, const QString &value, QHash<QString, AbstractRequestParam*>& params);
    inline static void writeFileBuf(QIODevice *writeDevice, int & pos, char*  buf, char c );
    inline static void writeFileBuf(QIODevice *file, int &pos, char *buf, int c);
    inline static int checkNotEof(int c);
    inline static void expectChar(int c, int expected);

    static void parseMultipart(QIODevice * writeDevice,const FCGX_Request & request, bool & foundFinalDelimiter, const QString &delimiter);

public:
 RequestData(const FCGX_Request & request, const QUrl &url);
    ~RequestData();
    const QString & getString(const QString&name) const;
    const QString & postString(const QString&name) const;
    int getInt(const QString&name) const;
    uint32_t getUInt(const QString&name) const;
    qint64 getInt64(const QString&name) const;
    int postInt(const QString&name) const;
    uint32_t postUInt(const QString&name) const;
    qint64 postInt64(const QString&name) const;
    double postDouble(const QString&name) const;
    double getDouble(const QString&name) const;
    bool postBool(const QString&name) const;
    const ArrayRequestParam & getArray(const QString&name) const;
    const ArrayRequestParam & postArray(const QString&name) const;
    const StringKeyArrayParam & postStringKeyArray(const QString&name) const;
    const StringKeyArrayParam & getStringKeyArray(const QString &name) const;
    QString getArrayValueString(const QString &name, const QString &key) const;
    QString getArrayValueString(const QString &name, int index) const;
    int getArrayValueInt(const QString &name, const QString &key) const;
    int getArrayValueInt(const QString &name, int index) const;
    bool isGetParamSet(const QString&name) const;
    bool isPostParamSet(const QString&name) const;
    QStringList postFieldNames() const;
    const UploadedFile & uploadedFile(const QString&fieldname) const;
    const UploadedFileArray & uploadedFileArray(const QString&fieldname) const;
    const UploadedFileStringKeyArray & uploadedFileArrayStringKey(const QString&fieldname) const;
    QVector<int> getIntArray(const QString&name) const;
    QVector<int> postIntArray(const QString&name) const;



};

#endif // REQUESTDATA_H
