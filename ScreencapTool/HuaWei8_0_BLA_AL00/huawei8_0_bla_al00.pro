

QT += core widgets
CONFIG += plugin

TARGET = huawei_mate_10
TEMPLATE = lib


HEADERS += \
    $$PWD/huawei8_0_bla_al00.h \
    $$PWD/createhuawei8_0_bla_al00.h \
    screentool.h

SOURCES += \
    $$PWD/huawei8_0_bla_al00.cpp \
    $$PWD/createhuawei8_0_bla_al00.cpp \
    screentool.cpp
