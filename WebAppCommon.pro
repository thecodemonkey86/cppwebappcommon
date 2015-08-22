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
#    controller/controllermanager.cpp \
#    controller_factory/controllerfactory.cpp \
    core/httpheader.cpp \
    controller/form.cpp \
    controller/formget.cpp \
    controller/formpost.cpp \
    controller/multiactioncontroller.cpp \
    controller/action/action.cpp \
    core/postdata.cpp \
    controller/action/formaction.cpp \
    view/formtemplate.cpp \
    view/formhtmltemplate.cpp \
    core/abstractobjectfactory.cpp \
    controller/controllermanager.cpp \
#    controller_factory/controllerfactory.cpp \
    page_config/pageconfig.cpp

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
#    controller_factory/controllerfactory.h \
    controller/abstractcontroller.h \
    controller/pagecontroller.h \
#    controller/controllermanager.h \
    core/httpheader.h \
    controller/form.h \
    controller/formget.h \
    controller/formpost.h \
    controller/multiactioncontroller.h \
    controller/action/action.h \
    core/postdata.h \
    controller/action/formaction.h \
    view/formtemplate.h \
    view/formhtmltemplate.h \
    core/objectfactory.h \
    core/abstractobjectfactory.h \
    controller/controllermanager.h \
#    controller_factory/controllerfactory.h \
    page_config/pageconfig.h
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
