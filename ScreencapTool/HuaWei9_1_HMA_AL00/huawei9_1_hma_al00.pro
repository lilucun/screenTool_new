


QT += core widgets
CONFIG += plugin

TARGET = huawei_mate_20
TEMPLATE = lib



HEADERS += \
    $$PWD/huawei9_1_hma_al00.h \
    $$PWD/createhuawei9_1_hma_al00.h \
    ../screentool.h

SOURCES += \
    $$PWD/huawei9_1_hma_al00.cpp \
    $$PWD/createhuawei9_1_hma_al00.cpp \
    ../screentool.cpp


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
