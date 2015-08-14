#ifndef ABSTRACTTEMPLATE_H
#define ABSTRACTTEMPLATE_H
#include <QTextStream>
#include "webappcommon_global.h"
#include <QDebug>
#include "abstractview.h"
#include <QFile>
#include "qtcout.h"


#ifndef output
#define output (*outStream)
//#define out (qDebug())
#endif

class WEBAPPCOMMONSHARED_EXPORT AbstractTemplate : public AbstractView
{
public:
    AbstractTemplate();
    ~AbstractTemplate();
   /* static void init() {
        f->open(QFile::Truncate| QFile::WriteOnly);
    }*/

    virtual void update();
    virtual void render()=0;
protected: static QtCout * outStream;
     //static QFile* f;
//protected: inline AbstractTemplate* out(const QString&s) {
//(*outStream)<<s;
//        return this;
//    }

};

#endif // ABSTRACTTEMPLATE_H
