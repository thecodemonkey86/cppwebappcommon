#-------------------------------------------------
#
# Project created by QtCreator 2015-07-25T12:18:49
#
#-------------------------------------------------
QT += sql
QT       -= gui

TARGET = WebAppCommon
TEMPLATE = lib

CONFIG += c++14

DEFINES += WEBAPPCOMMON_LIBRARY


CONFIG(release, debug|release) {
    QMAKE_CFLAGS_RELEASE -= -O
    QMAKE_CFLAGS_RELEASE -= -O1
    QMAKE_CFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
}

SOURCES += webappcommon.cpp \
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
    core/httpheader.cpp \
    page_config/pageconfig.cpp \
    page_config/pagemanager.cpp \
    mvc/mvcmessage.cpp \
    view/template/compiledtemplate.cpp \
    controller/abstractpagecontroller.cpp \
    controller/action/abstractaction.cpp \
    controller/multiactioncontroller.cpp \
    mvc/pagemvcmessage.cpp \
    form/formpost.cpp \
    form/formget.cpp \
    form/form.cpp \
    view/abstractview.cpp \
    controller/formpagecontroller.cpp \
    page_config/pagemanager2.cpp \
    core/sessiondata.cpp \
    view/template/htmltemplate.cpp \
    view/html/html.cpp \
    view/html/htmlselect.cpp \
    view/html/htmlrenderable.cpp \
    view/html/htmlautoclosetag.cpp \
    view/html/htmltag.cpp \
    view/html/htmlselectoption.cpp \
    view/html/htmltext.cpp


HEADERS += webappcommon.h\
        webappcommon_global.h \
    view/abstractview.h \
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
    page_config/pageconfig.h \
    page_config/pagemanager.h \
    mvc/mvcmessage.h \
    view/template/htmltemplate.h \
    view/template/compiledtemplate.h \
    controller/action/abstractaction.h \
    controller/abstractpagecontroller.h \
    controller/multiactioncontroller.h \
    mvc/pagemvcmessage.h \
    form/formpost.h \
    form/formget.h \
    form/form.h \
    controller/formpagecontroller.h \
    page_config/pagemanager2.h \
    fastcgicout.h \
    core/sessiondata.h \
    view/html/html.h \
    view/html/htmlselect.h \
    view/html/htmlrenderable.h \
    view/html/htmlautoclosetag.h \
    view/html/htmltag.h \
    view/html/htmlselectoption.h \
    view/html/htmltext.h

 #core/stringgetparam.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtCommon-Desktop_Qt_5_6_0_MinGW_32bit/release/ -lQtCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtCommon-Desktop_Qt_5_6_0_MinGW_32bit/debug/ -lQtCommon

INCLUDEPATH += ../QtCommon

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_6_0_MinGW_32bit/release/ -lSqlUtil2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_6_0_MinGW_32bit/debug/ -lSqlUtil2

INCLUDEPATH += $$PWD/../SqlUtil2


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-libfcgi-Desktop_Qt_5_6_0_MinGW_32bit/release/ -llibfcgi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-libfcgi-Desktop_Qt_5_6_0_MinGW_32bit/debug/ -llibfcgi
INCLUDEPATH += $$PWD/../libfcgi/include

QMAKE_RPATHDIR += $$PWD
