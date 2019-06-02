#ifndef WEBAPPCOMMON_GLOBAL_H
#define WEBAPPCOMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#include <QPair>
#include <QString>

#if defined(WEBAPPCOMMON_LIBRARY)
#  define WEBAPPCOMMONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEBAPPCOMMONSHARED_EXPORT Q_DECL_IMPORT
#endif
inline QPair<QString,QString> GetParam(const QString &name,const QString &value){
    return QPair<QString,QString>(name,value);
}

inline QPair<QString,QString> GetParam(const QString &name,int value){
    return QPair<QString,QString>(name,QString::number(value));
}

#endif // WEBAPPCOMMON_GLOBAL_H
