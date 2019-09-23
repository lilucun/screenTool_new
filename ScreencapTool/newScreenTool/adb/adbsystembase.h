#ifndef ADBSYSTEMBASE_H
#define ADBSYSTEMBASE_H

#include <QString>
#include <QEventLoop>
#include <QMutex>
#include "../phones/phones.h"

class AdbSystemBase
{
public:
//    AdbSystemBase();
    AdbSystemBase(const QString &serial);

    void initAdbStr();
    const QString getPicPath();
    void clickScreen(int pox_x, int pox_y, int delay_ms);

    void cutAnImage(const QString &picDir, const QString &picName, int delay_ms);

    void startActivity(const QString& act_name);
    void restartActvity(const QString& appName);
    void swipeScreen(int begin_x, int begin_y, int end_x, int end_y, int delay_ms);
    void verticalRollToBottom();
    void verticalRollToTop();

    void expandNotifactionHalf();
    void expandNotifactionFull();
    void clickLongTime(int pox_x, int pox_y, int delay_ms);
    void returnHome();
    void addVolumes();
    void delVolumes();

    void collapseKeyboard();
    void inputText(const QString & text);
    void delTextTens();
    void delTexts(int n);

    void commondAdbNoResults(const QString& commd);
    int commondAdbHasResults(const QString &commd, char *outResult);
    void commondAdbNoShell(const QString &commd);

    void delayMS(int ms);
    bool devIsDisConn(char *buf);

    void mkDirInitPicPath();

    virtual void swipeHalfCutImage(int begin_x, int begin_y, int end_x, int end_y,const QString & picDir,const QString & picName)=0;
    virtual void clickCancelCutImage(int pox_x, int pox_y, int delayMs,const QString & picDir,const QString & picName )=0;

protected:
    QString adbPrefix;
    QString adbExePath;

    static QMutex mutex;
    QString picPath;
    QString timeTemp;
    //AdbProcess adbProcess;
    QEventLoop loop;//延时
    QString serial;
};

#endif // ADBSYSTEMBASE_H
