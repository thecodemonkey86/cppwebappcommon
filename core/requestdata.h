#pragma once

#include "webappcommon_global.h"
#include <QHash>
#include <QIODevice>
#include <exception/qtexception.h>
class AbstractRequestParam;
class AbstractUploadedFile;
class ArrayRequestParam;
class QUrl;
class QString;
class StringKeyArrayParam;
class UploadedFile;
class UploadedFileArray;
class UploadedFileStringKeyArray;
struct FCGX_Request;


class WEBAPPCOMMONSHARED_EXPORT RequestData
{
private:
    static constexpr char CR = '\r';
    static constexpr char NL = '\n';
    static constexpr char HYPHEN = '-';
    static constexpr int BUF_SIZE = 8192;
    static int maxPostSize;
    QHash<QString, AbstractRequestParam*> getParams;
    QHash<QString, AbstractRequestParam*> postParams;
    QVector<AbstractUploadedFile*> uploadFiles;


    void parseGetParams(const QUrl& url);
    void parsePostParams(const FCGX_Request & request);

    static void addToHashtable(const QString & fieldName, const QString &value, QHash<QString, AbstractRequestParam*>& params);
    inline static void writeFileBuf(QIODevice *writeDevice, int & pos, char*  buf, char c )
    {
      buf[pos++] = c;
      if(pos == BUF_SIZE) {
        writeDevice->write(buf, BUF_SIZE);
        pos = 0;
      }
    }
    inline static void writeFileBuf(QIODevice *writeDevice, int &pos, char *buf, int c)
    {
      buf[pos++] = static_cast<char>(c);
      if(pos == BUF_SIZE) {
        writeDevice->write(buf, BUF_SIZE);
        pos = 0;
      }
    }
    inline static int checkNotEof(int c)
    {
      if(c==-1)
        throwExceptionWithLine("unexpected end of stream");
      return c;
    }
    inline static void expectChar(int c, int expected)
    {
      if(c!=expected)
        throwExceptionWithLine(QStringLiteral("expected character %1 but got %2").arg(static_cast<char>(expected),c));
    }

    static void parseMultipart(QIODevice * writeDevice,const FCGX_Request & request, bool & foundFinalDelimiter, const QString &delimiter);

public:
 RequestData(const FCGX_Request & request, const QUrl &url);
    ~RequestData();
    const QString & getString(const QString&name) const;
    const QString & getStringNoCheckForExistance(const QString&name) const;
    const QString & postString(const QString&name) const;
    int getInt(const QString&name) const;
    uint32_t getUInt(const QString&name) const;
    qint64 getInt64(const QString&name) const;
    int postInt(const QString&name) const;
    uint32_t postUInt(const QString&name) const;
    qint64 postInt64(const QString&name) const;
    double postDouble(const QString&name) const;
    double getDouble(const QString&name) const;
    bool getBool(const QString&name) const;
    bool postBool(const QString&name) const;
    ArrayRequestParam* getArray(const QString&name) const;
    ArrayRequestParam* postArray(const QString&name) const;
    StringKeyArrayParam* postStringKeyArray(const QString&name) const;
    StringKeyArrayParam* getStringKeyArray(const QString &name) const;
    QString getArrayValueString(const QString &name, const QString &key) const;
    QString getArrayValueString(const QString &name, int index) const;
    int getArrayCount(const QString &name) const;
    int postArrayCount(const QString &name) const;
    int getArrayValueInt(const QString &name, const QString &key) const;
    int getArrayValueInt(const QString &name, int index) const;
    bool isGetParamSet(const QString&name) const;
    bool isPostParamSet(const QString&name) const;
    QStringList postFieldNames() const;
    const UploadedFile & uploadedFile(const QString&fieldname) const;
    const UploadedFileArray & uploadedFileArray(const QString&fieldname) const;
    const UploadedFileStringKeyArray & uploadedFileArrayStringKey(const QString&fieldname) const;
    bool isUploadedFileSet(const QString&fieldname) const;
    QVector<int> getIntArray(const QString&name) const;
    QVector<int64_t> getInt64Array(const QString&name) const;
    QVector<int> postIntArray(const QString&name) const;
    QVector<int64_t> postInt64Array(const QString&name) const;
    QStringList getStringArray(const QString&name) const;
    QStringList postStringArray(const QString&name) const;
    QSet<int64_t> getInt64HashSet(const QString&name) const;
    QSet<int64_t> postInt64HashSet(const QString &name) const;
    static void setMaxPostSize(int newMaxPostSize);
};
