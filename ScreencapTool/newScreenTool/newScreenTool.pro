#-------------------------------------------------
#
# Project created by QtCreator 2019-07-22T17:04:03
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newScreenTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += SERVER_TEST # SERVER_USE RUIHONG_TEST
#DEFINES += SERVER_USE
#DEFINES += RUIHONG_TEST
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#LIBS += -static-libstdc++ -static-libgcc

SOURCES += \
        main.cpp \
    widget.cpp \
    getphoneobject.cpp



HEADERS += \
    widget.h \
    getphoneobject.h



FORMS += \
    widget.ui

include(adb/adb.pri)
include(manager/manager.pri)
include(phones/phones.pri)
include(worker/worker.pri)
include(others/others.pri)

INCLUDEPATH += \
        $$PWD/adb \
         $$PWD/manager \
         $$PWD/phones \
         $$PWD/worker \
         $$PWD/others

# 编译输出配置
win32 {
    contains(QT_ARCH, x86_64) { #x64平台
        message("x64 config")
        CONFIG(debug, debug|release) { #含debug
            DESTDIR = $$PWD/../output/win-x64/debug

        } else {
            DESTDIR = $$PWD/../output/win-x64/release
        }

    } else { #x86
        message("x86 config")
        CONFIG(debug, debug|release) { #含debug
            DESTDIR = $$PWD/../output/win-x86/debug

            # 添加 vld 检查
            DEFINES += VLD_CONFIG # 定义宏
            #VLD_PATH = $$PWD/../output/win-x86/debug/libs/vld
            #INCLUDEPATH += $${VLD_PATH}/include
            #LIBS += $${VLD_PATH}/bin/Win32 -lvld
        } else {
            DESTDIR = $$PWD/../output/win-x86/release
        }
    }

}




