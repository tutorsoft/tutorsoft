#-------------------------------------------------
#
# Project created by QtCreator 2019-04-23T17:50:06
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += no_batch
TARGET = TutorSystem

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/main.cpp\
    src/form/childwidgeta.cpp \
        src/mainwidget.cpp \
    src/loginwidget.cpp \
    src/signalmanageobject/signalmanageobject.cpp \
    src/database/userdatabase.cpp \
    src/qxmessagebox/qxmessagebox.cpp \
    src/sliderbar/sliderbar.cpp \ 
    src/form/childwidgeta.cpp \
    src/form/childwidgetb.cpp \
    src/form/childwidgetc.cpp \
    src/form/childwidgetd.cpp \
    src/form/childwidgete.cpp \
    src/teacherwidget.cpp \
    src/studentwidget.cpp \
    src/registerstudentwidget.cpp \
    src/registerteacherwidget.cpp \
    src/form/childwidgetf.cpp \
    src/form/childwidgetg.cpp \
    src/form/childwidgeth.cpp \
    src/form/childwidgeti.cpp \
    src/form/childwidgetj.cpp \
    src/form/childwidgetk.cpp \
    src/form/qfinddialog.cpp


HEADERS  += src/mainwidget.h \
    src/form/childwidgeta.h \
    src/loginwidget.h \
    src/signalmanageobject/signalmanageobject.h \
    src/database/userdatabase.h \
    src/qxmessagebox/qxmessagebox.h \
    src/sliderbar/sliderbar.h \ 
    src/form/childwidgeta.h \
    src/form/childwidgetb.h \
    src/form/childwidgetc.h \
    src/form/childwidgetd.h \
    src/form/childwidgete.h \
    src/teacherwidget.h \
    src/studentwidget.h \
    src/registerstudentwidget.h \
    src/registerteacherwidget.h \
    src/form/childwidgetf.h \
    src/form/childwidgetg.h \
    src/form/childwidgeth.h \
    src/form/childwidgeti.h \
    src/form/childwidgetj.h \
    src/form/childwidgetk.h \
    src/form/qfinddialog.h



FORMS    += \
    src/form/childwidgeta.ui \
    src/form/childwidgetb.ui \
    src/form/childwidgetc.ui \
    src/form/childwidgetd.ui \
    src/form/childwidgete.ui \
    src/form/childwidgetf.ui \
    src/form/childwidgetg.ui \
    src/form/childwidgeth.ui \
    src/form/childwidgeti.ui \
    src/form/childwidgetj.ui \
    src/form/childwidgetk.ui \
    src/form/qfinddialog.ui


DESTDIR         += $$PWD/bin
TEMPLATE        = app
MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
CONFIG          += qt warn_off
win32:RC_FILE   = other/main.rc

RESOURCES += \
    other/qss.qrc \
    other/main.qrc \
    demo.qrc \
    image.qrc
