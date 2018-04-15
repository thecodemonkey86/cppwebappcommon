#-------------------------------------------------
#
# Project created by QtCreator 2015-07-25T12:18:49
#
#-------------------------------------------------
QT += sql network
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
    page_config/pagemanager2.cpp \
    core/sessiondata.cpp \
    view/template/htmltemplate.cpp \
    view/html/htmlselect.cpp \
    view/html/htmlrenderable.cpp \
    view/html/htmlautoclosetag.cpp \
    view/html/htmltag.cpp \
    view/html/htmlselectoption.cpp \
    view/html/htmltext.cpp \
    view/html/util/htmlutil.cpp \
    core/uploadedfile.cpp \
    core/abstractuploadedfile.cpp \
    core/uploadedfilearray.cpp \
    core/uploadedfilestringkeyarray.cpp


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
    page_config/pagemanager2.h \
    fastcgicout.h \
    core/sessiondata.h \
    view/html/html.h \
    view/html/htmlselect.h \
    view/html/htmlrenderable.h \
    view/html/htmlautoclosetag.h \
    view/html/htmltag.h \
    view/html/htmlselectoption.h \
    view/html/htmltext.h \
    view/html/util/htmlutil.h \
    core/uploadedfile.h \
    core/abstractuploadedfile.h \
    core/uploadedfilearray.h \
    core/uploadedfilestringkeyarray.h

 #core/stringgetparam.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
        CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_9_0_MinGW_32bit/release/ -lQtCommon2
        CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_9_0_MinGW_32bit/debug/ -lQtCommon2

        INCLUDEPATH += ../QtCommon2

        CONFIG(release, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_9_0_MinGW_32bit/release/ -lSqlUtil2
        CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_9_0_MinGW_32bit/debug/ -lSqlUtil2

        INCLUDEPATH += $$PWD/../SqlUtil2
        CONFIG(release, debug|release): LIBS += -L$$PWD/../build-libfcgi-Desktop_Qt_5_9_0_MinGW_32bit/release/ -llibfcgi
        CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-libfcgi-Desktop_Qt_5_9_0_MinGW_32bit/debug/ -llibfcgi
        INCLUDEPATH += $$PWD/../libfcgi/include
}

win32-msvc* {
        CONFIG(release, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_10_1_MSVC2017_64bit/release/ -lSqlUtil2
        else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_10_1_MSVC2017_64bit/debug/ -lSqlUtil2

        CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_10_1_MSVC2017_64bit/release/ -lQtCommon2
        else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_10_1_MSVC2017_64bit/debug/ -lQtCommon2


        CONFIG(release, debug|release): LIBS += -L$$PWD/../build-libfcgi-Desktop_Qt_5_10_1_MSVC2017_64bit/release/ -llibfcgi
        else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-libfcgi-Desktop_Qt_5_10_1_MSVC2017_64bit/debug/ -llibfcgi

}


INCLUDEPATH += $$PWD/../QtCommon2
INCLUDEPATH += $$PWD/../SqlUtil2
INCLUDEPATH += $$PWD/../libfcgi/include

unix {
        CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_11_0_GCC_64bit/release/ -lQtCommon2
        CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_11_0_GCC_64bit/debug/ -lQtCommon2

        INCLUDEPATH += ../QtCommon2

        CONFIG(release, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_11_0_GCC_64bit/release/ -lSqlUtil2
        CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-SqlUtil2-Desktop_Qt_5_11_0_GCC_64bit/debug/ -lSqlUtil2

        INCLUDEPATH += $$PWD/../SqlUtil2

        CONFIG(release, debug|release): LIBS += -lfcgi++ -lfcgi
        CONFIG(debug, debug|release): LIBS += -lfcgi++ -lfcgi
        INCLUDEPATH += $$PWD/../libfcgi/include

}


QMAKE_RPATHDIR += $$PWD
