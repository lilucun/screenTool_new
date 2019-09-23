


QT += core widgets
CONFIG += plugin

TARGET = huawei8_0_bkl_al00
TEMPLATE = lib



HEADERS += \
    $$PWD/huawei8_0_bkl_al00.h \
    $$PWD/createhuawei8_0_bkl_al00.h \
    imagecompare.h \
    ../screentool.h


SOURCES += \
    $$PWD/huawei8_0_bkl_al00.cpp \
    $$PWD/createhuawei8_0_bkl_al00.cpp \
    imagecompare.cpp \
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


INCLUDEPATH +=  E:\opencv\OpenCV_3.4.3-Build\install\include \
                 E:\opencv\OpenCV_3.4.3-Build\install\include\opencv \
                 E:\opencv\OpenCV_3.4.3-Build\install\include\opencv2
LIBS +=  E:\opencv\OpenCV_3.4.3-Build\lib\libopencv_*a


