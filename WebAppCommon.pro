#-------------------------------------------------
#
# Project created by QtCreator 2015-07-25T12:18:49
#
#-------------------------------------------------
QT += sql
QT       -= gui

TARGET = WebAppCommon
TEMPLATE = lib

CONFIG += c++11

DEFINES += WEBAPPCOMMON_LIBRARY

SOURCES += webappcommon.cpp \
    view/template/abstracttemplate.cpp \
    view/template/htmltemplate.cpp \
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
#    controller/controllermanager.cpp \
#    controller_factory/controllerfactory.cpp \
    core/httpheader.cpp \
    controller/form.cpp \
    controller/formget.cpp \
    controller/formpost.cpp \
    controller/action/formaction.cpp \
    view/template/formhtmltemplate.cpp \
    core/abstractobjectfactory.cpp \
    controller/controllermanager.cpp \
#    controller_factory/controllerfactory.cpp \
    page_config/pageconfig.cpp \
    page_config/pagemanager.cpp \
    mvc/mvcmessage.cpp \
    view/formview.cpp \
    view/template/formtemplate.cpp \
    view/template/compiledtemplate.cpp \
    controller/abstractpagecontroller.cpp \
    controller/action/abstractaction.cpp \
    model/beans/session.cpp \
    model/beans/sessionvalue.cpp \
    model/sessiondata.cpp \
    controller/multiactioncontroller.cpp \
    mvc/pagemvcmessage.cpp

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
    controller/abstractcontroller.h \
    core/httpheader.h \
    controller/form.h \
    controller/formget.h \
    controller/formpost.h \
    controller/action/formaction.h \
    view/template/formhtmltemplate.h \
    core/objectfactory.h \
    core/abstractobjectfactory.h \
    controller/controllermanager.h \
    page_config/pageconfig.h \
    page_config/pagemanager.h \
    mvc/mvcmessage.h \
    view/formview.h \
    view/template/formtemplate.h \
view/template/htmltemplate.h \
view/template/abstracttemplate.h \
    view/template/compiledtemplate.h \
    controller/action/abstractaction.h \
    controller/abstractpagecontroller.h \
    model/beans/session.h \
    model/beans/sessionvalue.h \
    model/sessiondata.h \
    controller/multiactioncontroller.h \
    mvc/pagemvcmessage.h
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
