#-------------------------------------------------
#
# Project created by QtCreator 2015-07-25T12:18:49
#
#-------------------------------------------------
QT += sql
QT       -= gui

TARGET = WebAppCommon
TEMPLATE = lib

DEFINES += WEBAPPCOMMON_LIBRARY

SOURCES += webappcommon.cpp \
    view/abstracttemplate.cpp \
    view/htmltemplate.cpp \
    view/abstractview.cpp \
    qtcout.cpp \
    core/requestdata.cpp \
    core/serverdata.cpp \
    #core/stringgetparam.cpp
    core/arrayvalue.cpp \
    core/abstractstringkeyarrayparam.cpp \
    core/stringkeyarrayparam.cpp \
    core/abstractrequestparam.cpp \
    core/arrayrequestparam.cpp \
    util/util.cpp \
    controller/abstractcontroller.cpp \
    controller/pagecontroller.cpp \
    controller/controllermanager.cpp \
    controller_factory/controllerfactory.cpp \
    core/sessiondata.cpp \
    core/httpheader.cpp \
    model/beans/session.cpp \
    model/beans/sessionvalue.cpp

HEADERS += webappcommon.h\
        webappcommon_global.h \
    view/abstracttemplate.h \
    view/htmltemplate.h \
    view/abstractview.h \
    qtcout.h \
    core/requestdata.h \
    core/serverdata.h \
    core/arrayvalue.h \
    core/abstractstringkeyarrayparam.h \
    core/stringkeyarrayparam.h \
    core/abstractrequestparam.h \
    core/requestparam.h \
    core/arrayrequestparam.h \
    util/util.h \
    controller_factory/controllerfactory.h \
    controller/abstractcontroller.h \
    controller/pagecontroller.h \
    controller/controllermanager.h \
    core/sessiondata.h \
    core/httpheader.h \
    model/beans/session.h \
    model/beans/sessionvalue.h
 #core/stringgetparam.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtCommon-Desktop_Qt_5_5_0_GCC_64bit/release/ -lQtCommon
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtCommon-Desktop_Qt_5_5_0_GCC_64bit/debug/ -lQtCommon

INCLUDEPATH += ../QtCommon

unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-ORM-Desktop_Qt_5_5_0_GCC_64bit/release/ -lORM
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-ORM-Desktop_Qt_5_5_0_GCC_64bit/debug/ -lORM

INCLUDEPATH += $$PWD/../ORM

unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_5_0_GCC_64bit/release/ -lSqlUtil2
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_5_0_GCC_64bit/debug/ -lSqlUtil2

INCLUDEPATH += ../SqlUtil2
