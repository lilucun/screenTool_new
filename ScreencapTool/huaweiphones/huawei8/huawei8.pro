QT += core widgets xml
CONFIG += plugin

TARGET = huawei8
TEMPLATE = lib

HEADERS += \
    $$PWD/huawei8factory.h \
    $$PWD/huaweiphones8.h \
    ../../newScreenTool/phones/huaweiphones.h \
    ../../newScreenTool/phones/phonesfactory.h \
    ../../newScreenTool/adb/adbsystembase.h \
    ../../newScreenTool/adb/adbsystemhuawei.h \
    ../../newScreenTool/phones/phones.h \
    ../../newScreenTool/phones/phonesfactory.h \
    imagecompare.h

SOURCES += \
    $$PWD/huaweiphones8.cpp \
    $$PWD/huawei8factory.cpp \
    ../../newScreenTool/phones/huaweiphones.cpp \
    ../../newScreenTool/adb/adbsystembase.cpp \
    ../../newScreenTool/adb/adbsystemhuawei.cpp \
    ../../newScreenTool/phones/phones.cpp \
    ../../newScreenTool/phones/phonesfactory.cpp \
    imagecompare.cpp


INCLUDEPATH += \
    $$PWD/../newScreenTool/adb\
     $$PWD/../newScreenTool/phones


LIBS += -L$$PWD/../../output/ocrLib -locrTest
INCLUDEPATH += $$PWD/../../output/ocrLib

INCLUDEPATH +=  E:\opencv\OpenCV_3.4.3-Build\install\include \
                 E:\opencv\OpenCV_3.4.3-Build\install\include\opencv \
                 E:\opencv\OpenCV_3.4.3-Build\install\include\opencv2
LIBS +=  E:\opencv\OpenCV_3.4.3-Build\lib\libopencv_*a

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
