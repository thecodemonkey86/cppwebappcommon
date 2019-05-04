#ifndef WEBAPPCOMMON_GLOBAL_H
#define WEBAPPCOMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#include <QPair>

#if defined(WEBAPPCOMMON_LIBRARY)
#  define WEBAPPCOMMONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEBAPPCOMMONSHARED_EXPORT Q_DECL_IMPORT
#endif

typedef QPair<QString,QString> GetParam;

#endif // WEBAPPCOMMON_GLOBAL_H
