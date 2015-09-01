#ifndef ABSTRACTTEMPLATE_H
#define ABSTRACTTEMPLATE_H
#include <QTextStream>
#include "webappcommon_global.h"
#include <QDebug>
#include "view/abstractview.h"
#include <QFile>
#include "qtcout.h"
#include "mvc/mvcmessage.h"

#ifndef output
#define output (*outStream)
//#define out (qDebug())
#endif

class WEBAPPCOMMONSHARED_EXPORT AbstractTemplate : public AbstractView
{
public:
    AbstractTemplate();
    virtual ~AbstractTemplate();
//    static QString&encodeHtml(const QString&);

protected: static QtCout * outStream;


};

#endif // ABSTRACTTEMPLATE_H
