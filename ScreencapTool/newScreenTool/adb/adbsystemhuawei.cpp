#include "adbsystemhuawei.h"
#include <QTime>
#include <QtConcurrent/QtConcurrent>

AdbSystemHuaWei::AdbSystemHuaWei(const QString &serial):AdbSystemBase(serial)
{

}

void AdbSystemHuaWei::setBaseScreenSize(const ScreenSizeT &baseScreenSize)
{
    this->baseScreenSize = baseScreenSize;
}

void AdbSystemHuaWei::setPhoneScreenSize(const ScreenSizeT &screenSize)
{
    this->phoneScreenSize = screenSize;
}

ScreenSizeT AdbSystemHuaWei::getBaseSize()
{
    return baseScreenSize;
}

ScreenSizeT AdbSystemHuaWei::getPhoneSize()
{
    return phoneScreenSize;
}

void AdbSystemHuaWei::clickScreen(int pox_x, int pox_y, int delay_ms, OprateStatus status)
{
     qDebug() << "pox" << pox_x << " " << pox_y;
    // 坐标转换
    //nx = int(120 / 1080.0 * int(dw));
    //ny = int(200 / 320.0 * int(dh));
    if(status == SCALING_POS){
        pox_x = (pox_x/ (float)baseScreenSize.width) * phoneScreenSize.width;
        pox_y = (pox_y/ (float)baseScreenSize.height) * phoneScreenSize.height;
    }

    if(status == RELATIVE_TOP_POS){
        pox_x = (pox_x/ (float)baseScreenSize.width) * phoneScreenSize.width;
        pox_y = phoneScreenSize.height -  baseScreenSize.height + pox_y;
    }
    qDebug() << "pox" << pox_x << " " << pox_y;
    AdbSystemBase::clickScreen(pox_x, pox_y, delay_ms);
}

void AdbSystemHuaWei::swipeScreen(int begin_x, int begin_y, int end_x, int end_y, int delay_ms)
{
    begin_x = (begin_x/ (float)baseScreenSize.width) * phoneScreenSize.width;
    begin_y = (begin_y/ (float)baseScreenSize.height) * phoneScreenSize.height;
    end_x = (end_x/ (float)baseScreenSize.width) * phoneScreenSize.width;
    end_y = (end_y/ (float)baseScreenSize.height) * phoneScreenSize.height;

    AdbSystemBase::swipeScreen(begin_x, begin_y, end_x, end_y, delay_ms);
}

void AdbSystemHuaWei::clickLongTime(int pox_x, int pox_y, int delay_ms, OprateStatus status)
{
    if(status == RELATIVE_TOP_POS){
        pox_x = (pox_x/ (float)baseScreenSize.width) * phoneScreenSize.width;
        pox_y = phoneScreenSize.height - (baseScreenSize.height - pox_y);
    }
    if(status == SCALING_POS){
        pox_x = (pox_x/ (float)baseScreenSize.width) * phoneScreenSize.width;
        pox_y = (pox_y/ (float)baseScreenSize.height) * phoneScreenSize.height;
    }


    AdbSystemBase::clickLongTime(pox_x, pox_y, delay_ms);
}


void cutImage(AdbSystemHuaWei* tool, const QString &picDir,const QString &picName, int dalayMs)
{


    QTime _time = QTime::currentTime().addMSecs(dalayMs);// 1s
    while (QTime::currentTime() < _time) {}
    tool->cutAnImage(picDir, picName, 10);
}

void AdbSystemHuaWei::swipeHalfCutImage(int begin_x, int begin_y, int end_x, int end_y, const QString &picDir, const QString &picName)
{
    begin_x = (begin_x/ (float)baseScreenSize.width) * phoneScreenSize.width;
    begin_y = (begin_y/ (float)baseScreenSize.height) * phoneScreenSize.height;
    end_x = (end_x/ (float)baseScreenSize.width) * phoneScreenSize.width;
    end_y = (end_y/(float) baseScreenSize.height) * phoneScreenSize.height;

    QtConcurrent::run(cutImage, this, picDir, picName, 1900);
//    AdbSystemBase::swipeScreen(begin_x, begin_y, end_x, end_y, 3000);
    commondAdbNoResults(QString("input swipe %1 %2 %3 %4 %5").arg(begin_x).arg(begin_y).arg(end_x).arg(end_y).arg(3000));
}

void AdbSystemHuaWei::clickCancelCutImage(int pox_x, int pox_y, int delayMs, const QString &picDir, const QString &picName)
{
    QtConcurrent::run(cutImage, this, picDir, picName, 1800);
    clickLongTime(pox_x, pox_y, delayMs);
}

