#ifndef ADBSYSTEMHUAWEI_H
#define ADBSYSTEMHUAWEI_H

#include "adbsystembase.h"

// 不转换坐标 等比例缩放坐标 相对底部坐标
enum OprateStatus{NO_CONV_POS, SCALING_POS, RELATIVE_TOP_POS};

class AdbSystemHuaWei : public AdbSystemBase
{
    friend void cutImage(AdbSystemHuaWei* tool, const QString & picDir,const QString & picName, int dalayMs);
public:
    AdbSystemHuaWei(const QString &serial);

    void setBaseScreenSize(const ScreenSizeT &baseScreenSize);
    void setPhoneScreenSize(const ScreenSizeT &screenSize);
    ScreenSizeT getBaseSize();
    ScreenSizeT getPhoneSize();

    void clickScreen(int pox_x, int pox_y, int delay_ms, OprateStatus status=SCALING_POS);

    void swipeScreen(int begin_x, int begin_y, int end_x, int end_y, int delay_ms);

    void clickLongTime(int pox_x, int pox_y, int delay_ms, OprateStatus status=RELATIVE_TOP_POS);

    void swipeHalfCutImage(int begin_x, int begin_y, int end_x, int end_y,const QString & picDir,const QString & picName);
    void clickCancelCutImage(int pox_x, int pox_y, int delayMs,const QString & picDir,const QString & picName );

protected:
    ScreenSizeT baseScreenSize;
    ScreenSizeT phoneScreenSize;
};

#endif // ADBSYSTEMHUAWEI_H
