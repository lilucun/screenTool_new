QT += core widgets xml
CONFIG += plugin

TARGET = huawei9
TEMPLATE = lib

HEADERS += \
    $$PWD/huaweiphones9.h \
    huawei9factory.h \
    ../../newScreenTool/phones/huaweiphones.h \
    ../../newScreenTool/phones/phonesfactory.h \
    ../../newScreenTool/adb/adbsystembase.h \
    ../../newScreenTool/adb/adbsystemhuawei.h \
    ../../newScreenTool/phones/phones.h \
    ../../newScreenTool/phones/phonesfactory.h
SOURCES += \
    $$PWD/huaweiphones9.cpp \
    huawei9factory.cpp \
    ../../newScreenTool/phones/huaweiphones.cpp \
    ../../newScreenTool/adb/adbsystembase.cpp \
    ../../newScreenTool/adb/adbsystemhuawei.cpp \
    ../../newScreenTool/phones/phones.cpp \
    ../../newScreenTool/phones/phonesfactory.cpp


LIBS += -L$$PWD/../../output/ocrLib -locrTest
INCLUDEPATH += $$PWD/../../output/ocrLib


win32 {
    contains(QT_ARCH, x86_64) { #x64平�??        message("x64 config")
        CONFIG(debug, debug|release) { #??ebug
            DESTDIR = $$PWD/../../output/lib/x64/debug

        } else {
            DESTDIR = $$PWD/../../output/lib/x64/release
        }

    } else { #x86
        message("x86 config")
        CONFIG(debug, debug|release) { #??ebug
            DESTDIR = $$PWD/../../output/lib/x86/debug

        } else {
            DESTDIR = $$PWD/../../output/lib/x86/release
        }
    }

}

DISTFILES += \
    a.txt
