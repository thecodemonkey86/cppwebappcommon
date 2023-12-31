#pragma once


#include <QtCore/qglobal.h>

#include <QPair>
#include <QString>

#if defined(WEBAPPCOMMON_LIBRARY)
#  define WEBAPPCOMMONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEBAPPCOMMONSHARED_EXPORT Q_DECL_IMPORT
#endif

