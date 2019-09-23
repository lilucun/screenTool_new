

QT += core widgets
CONFIG += plugin

TARGET = huawei_mate_10_pro
TEMPLATE = lib




HEADERS += \
    $$PWD/huawei8_0_bla_tl00.h \
    $$PWD/createhuawei8_0_bla_tl00.h \
    ../screentool.h

SOURCES += \
    $$PWD/huawei8_0_bla_tl00.cpp \
    $$PWD/createhuawei8_0_bla_tl00.cpp \
    ../screentool.cpp
