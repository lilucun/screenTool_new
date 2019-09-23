
QT += core widgets
CONFIG += plugin

TARGET = huawei8_0_duk_al20
TEMPLATE = lib


HEADERS += \
    $$PWD/huawei8_0_duk_al20.h \
    $$PWD/createhuawei8_0_duk_al20.h \
    screentool.h

SOURCES += \
    $$PWD/huawei8_0_duk_al20.cpp \
    $$PWD/createhuawei8_0_duk_al20.cpp \
    screentool.cpp


LIBS += -L$$PWD/../../output/ocrLib -locrTest
INCLUDEPATH += $$PWD/../../output/ocrLib

# 编译输出配置
win32 {
    contains(QT_ARCH, x86_64) { #x64平台
        message("x64 config")
        CONFIG(debug, debug|release) { #含debug
            DESTDIR = $$PWD/../../output/lib/x64/debug

        } else {
            DESTDIR = $$PWD/../../output/lib/x64/release
        }

    } else { #x86
        message("x86 config")
        CONFIG(debug, debug|release) { #含debug
            DESTDIR = $$PWD/../../output/lib/x86/debug

        } else {
            DESTDIR = $$PWD/../../output/lib/x86/release
        }
    }

}
