#-------------------------------------------------
#
# Project created by QtCreator 2019-05-31T18:43:43
#
#-------------------------------------------------
QT += core sql network
QT       -= gui

TARGET = WebAppCommon
TEMPLATE = lib

DEFINES += WEBAPPCOMMON_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


COMPILER = ""
ARCH = ""

msvc {

 COMPILER = "MSVC2017"
 MSVC_VER = $$(VisualStudioVersion)
 equals(MSVC_VER, 16.0){
     COMPILER = "MSVC2019"
 }

    equals(QMAKE_TARGET.arch, "x86_64"){
        ARCH = "64bit"
    } else {
         ARCH = "32bit"
    }

}

SOURCES += \
    core/requestparam.cpp \
    mvc/controller/abstractpagecontroller.cpp \
    core/abstractrequestparam.cpp \
    core/abstractstringkeyarrayparam.cpp \
    core/abstractuploadedfile.cpp \
    core/arrayrequestparam.cpp \
    core/arrayvalue.cpp \
    core/httpheader.cpp \
    core/page/pageconfig.cpp \
    core/page/pagemanager.cpp \
    core/requestdata.cpp \
    core/serverdata.cpp \
    core/sessiondata.cpp \
    core/stringkeyarrayparam.cpp \
    core/uploadedfile.cpp \
    core/uploadedfilearray.cpp \
    core/uploadedfilestringkeyarray.cpp \
    mvc/controller/action/abstractaction.cpp \
    mvc/controller/multiactionpagecontroller.cpp \
    mvc/view/abstractview.cpp \
    mvc/view/html/ajaxhtmlview.cpp \
    mvc/view/html/htmltemplate.cpp \
    mvc/view/html/linktag.cpp \
    mvc/view/html/metatag.cpp \
    mvc/view/jsonview.cpp \
    mvc/model/viewdata.cpp \
    util/form/form.cpp \
    util/form/formget.cpp \
    util/form/formpost.cpp

HEADERS += webappcommon_global.h \
    mvc/controller/abstractpagecontroller.h \
    core/abstractrequestparam.h \
    core/abstractstringkeyarrayparam.h \
    core/abstractuploadedfile.h \
    core/arrayrequestparam.h \
    core/arrayvalue.h \
    core/fastcgioutput.h \
    core/httpheader.h \
    core/page/pageconfig.h \
    core/page/pagemanager.h \
    core/requestdata.h \
    core/requestparam.h \
    core/serverdata.h \
    core/sessiondata.h \
    core/stringkeyarrayparam.h \
    core/uploadedfile.h \
    core/uploadedfilearray.h \
    core/uploadedfilestringkeyarray.h \
    mvc/controller/action/abstractaction.h \
    mvc/controller/multiactionpagecontroller.h \
    mvc/view/abstractview.h \
    mvc/view/html/ajaxhtmlview.h \
    mvc/view/html/htmltemplate.h \
    mvc/view/html/linktag.h \
    mvc/view/html/metatag.h \
    mvc/view/jsonview.h \
    mvc/model/viewdata.h \
    util/form/form.h \
    util/form/formget.h \
    util/form/formpost.h

msvc {
CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/libfcgi-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/release/ -llibfcgi
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/libfcgi-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/debug/ -llibfcgi

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/release/ -lQtCommon2
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/debug/ -lQtCommon2
}

INCLUDEPATH += $$PWD/../libfcgi/include
INCLUDEPATH += $$PWD/../QtCommon2

unix {
    target.path = /usr/lib
    INSTALLS += target
}
