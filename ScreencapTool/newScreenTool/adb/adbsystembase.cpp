#include "adbsystembase.h"
#include <QApplication>
#include <QProcess>
#include <QTime>
#include <QDir>
#include <QMutexLocker>
#include <QTimer>
#include <QDebug>
#include <QRegularExpression>


QMutex AdbSystemBase::mutex;

AdbSystemBase::AdbSystemBase(const QString& serial)
{
    this->serial = serial;
    initAdbStr();
}

void AdbSystemBase::initAdbStr()
{
    adbExePath = QApplication::applicationDirPath();
    adbExePath.append("/plugins/adb/adb.exe");

    adbPrefix.clear();
    adbPrefix.append(adbExePath);
    adbPrefix.append(" -s ");
    adbPrefix.append(serial);
    adbPrefix.append(" shell ");
}

const QString AdbSystemBase::getPicPath()
{
    return this->picPath;
}


void AdbSystemBase::clickScreen(int pox_x, int pox_y, int delay_ms)
{
    commondAdbNoResults(QString("input tap %1 %2").arg(pox_x).arg(pox_y));
    delayMS(delay_ms);
}


void AdbSystemBase::cutAnImage(const QString &picDir, const QString &picName, int delay_ms)
{
    Q_UNUSED(delay_ms);
    if (picPath.size() == 0) {
        qCritical("图片路径为null，截图失败！！！");
        return;
    }

 #if 0
    QProcess pro;
    pro.start("cmd",  QStringList() <<"/c" << QString("%1 screencap -p > %2.png").arg(adbPrefix).arg(timeTemp));
    //commondAdbNoResults(QString("screencap -p > %1.png").arg(timeTemp));

    pro.waitForFinished();
    QString tem;

    tem = QString("%1%2/_%3.png").arg(picPath).arg(picDir).arg(timeTemp);
    // 图片转换
    convertPng(QString("%1.png").arg(timeTemp).toStdString().c_str(), tem.toStdString().c_str());
    // 重命名
    QFile::rename(tem, QString("%1%2/%3").arg(picPath).arg(picDir).arg(picName));

    qDebug() << picDir << " " << picName;
    if(QFile::exists(QString("%1.png").arg(timeTemp)))
        QFile::remove(QString("%1.png").arg(timeTemp));
#elif 1
    //adb -s 66J0218C21005830  exec-out screencap -p > sc.png
    commondAdbNoResults(QString("screencap -p /sdcard/%1.png").arg(timeTemp));
    QString temp;
    temp.append(QString("pull /sdcard/%1.png  %2%3/%4").arg(timeTemp).arg(picPath).arg(picDir).arg(picName));

    delayMS(500);

    commondAdbNoShell(temp);
#else
    commondAdbNoShell(QString("exec-out screencap -p > %2%3/%4").arg(picPath).arg(picDir).arg(picName));

#endif

}



void AdbSystemBase::startActivity(const QString & act_name)
{
    if(act_name.size() == 0)
        return;

    char outBuf[1024] = "";
    // 参数 -W可以等待启动完成
    int ret = commondAdbHasResults(QString("am start -W %1").arg(act_name), outBuf);
    if (ret != 0) {
        qCritical() << "startActivity failed";
        return;
    }
    if (ret == 1)
        qCritical("手机断开");


    // 判断第一行结果
    if (QString(outBuf).contains("Starting: Intent")) {
        // 执行成功
        qDebug() << "startActivity执行成功";
    } else {
        qCritical() << "startActivity返回结果错误";
    }

    delayMS(400);

}

/* 滑动屏幕
*/
void AdbSystemBase::swipeScreen(int begin_x, int begin_y, int end_x, int end_y, int delay_ms)
{
    commondAdbNoResults(QString("input swipe %1 %2 %3 %4").arg(begin_x).arg(begin_y).arg(end_x).arg(end_y));
    delayMS(delay_ms);
}
/* 选中页面最底部的item(滑动到最底部)
 */
void AdbSystemBase::verticalRollToBottom()
{
    commondAdbNoResults("input roll 0 1000");
    delayMS(500);
}

/* 选中页面最顶部的item(滑动到最顶部)
 */
void AdbSystemBase::verticalRollToTop()
{
    commondAdbNoResults("input roll 0 -1000");
    delayMS(500);
}



void AdbSystemBase::restartActvity(const QString &appName)
{
    if(appName.size() == 0)
        return;
    // 参数-S可以先关闭 app 再启动activity
    commondAdbNoResults(QString("am start -S %1").arg(appName));

    delayMS(500);

}
/* 部分展开通知栏
*/
void AdbSystemBase::expandNotifactionHalf()
{
    commondAdbNoResults("cmd statusbar expand-notifications");
    delayMS(500);
}
/* 全部展开通知栏
*/
void AdbSystemBase::expandNotifactionFull()
{
    commondAdbNoResults("cmd statusbar expand-settings");
    delayMS(500);
}


void AdbSystemBase::clickLongTime(int pox_x, int pox_y, int delay_ms)
{
    commondAdbNoResults(QString("input swipe %1 %2 %3 %4 %5").arg(pox_x).arg(pox_y).arg(pox_x+1).arg(pox_y+1).arg(delay_ms));
    delayMS(200);
}


void AdbSystemBase::returnHome()
{
    commondAdbNoResults("input keyevent 3");
    delayMS(500);
}

void AdbSystemBase::addVolumes()
{
    commondAdbNoResults("input keyevent 24");
    delayMS(500);
}
// 音量减
void AdbSystemBase::delVolumes()
{
    commondAdbNoResults("input keyevent 25");
    delayMS(100);
}
/* 收起输入的软键盘
*/
void AdbSystemBase::collapseKeyboard()
{
    commondAdbNoResults("input keyevent 111");

    delayMS(400);
}
// 在输入框上输入内容
void AdbSystemBase::inputText(const QString &text)
{
    commondAdbNoResults(QString("input text %1").arg(text));

    delayMS(500);
}

void AdbSystemBase::delTextTens()
{
    delTexts(10);
}

void AdbSystemBase::delTexts(int n)
{
    for(int i = 0; i < n; ++i)
        commondAdbNoResults(QString("input keyevent 67"));
}



void AdbSystemBase::commondAdbNoResults(const QString &commd)
{
    // 判断 adbPrefix 是否为null
    if (adbPrefix.size() == 0)
        qCritical() << "adb 前缀未初始化";

    QString temp(adbPrefix);
    temp.append(commd);

    qDebug() << temp;
    QProcess pro;
    pro.execute(temp);

}


/*
 函数说明: commondAdbHasResults
 功能：执行有返回结果的adb命令
 参数：commd 是去除adb shell 后剩下的命令部分，outResult是命令执行的第一行结果
 返回值：
    -1 资源不足、打开失败
    1 手机断开或异常
    0 成功【需要判断返回第一行结果是否是预期内容】

*/

int AdbSystemBase::commondAdbHasResults(const QString&  commd, char *outResult)
{
    //
    if(outResult == NULL || adbPrefix.size() == 0)
        return -1;

    QString temp(adbPrefix);
    temp.append(commd);

    FILE *fp = NULL;
    char buf[1024] = "";

    qDebug() << temp;

    fp = _popen(temp.toStdString().c_str(), "r");
    if (fp == NULL) {
        //
        qCritical() << "popen failed...";
        return -1;
    }

    if (NULL != fgets(buf, sizeof(buf), fp)) {
        //
        if (devIsDisConn(buf)) {
            _pclose(fp);
            fp = NULL;
            return 1;
        }

        strncpy(outResult, buf, strlen(buf) - 1);
        _pclose(fp);
        fp = NULL;
        return 0;

    }

    if(fp != NULL)
        _pclose(fp);

    return -1;

}

void AdbSystemBase::commondAdbNoShell(const QString &commd)
{
    // 判断 adbPrefix 是否为null
    QString temp(adbExePath);
    temp.append(" -s ");
    temp.append(this->serial);
    temp.append("  ");
    temp.append(commd);

    qDebug() << temp;

    QProcess pro;
    pro.execute(temp);
    //system(temp.toStdString().c_str());

}

bool AdbSystemBase::devIsDisConn(char *buf)
{
    if(buf == NULL)
        return false;

    QRegularExpression reg("^error: device \'.+\' not found");
    return (QString(buf).contains(reg));
}

void AdbSystemBase::mkDirInitPicPath()
{
    // 加锁，减少冲突
    QMutexLocker lock(&mutex);

    if (!picPath.isEmpty())
        picPath.clear();
    // get exe dir 目录不能有空格等非标准命名
    picPath.append(QCoreApplication::applicationDirPath());
    // get time

    picPath.append("/temp");
    QDir dir(picPath);
    if(!dir.exists())
        dir.mkdir(picPath);
    picPath.append("/");

    QDateTime currenTime = QDateTime::currentDateTime();
    timeTemp = currenTime.toString("yyyy_MM_dd_hh_mm_ss");
    picPath.append(timeTemp);

    dir.setPath(picPath);

    if (!dir.exists()) {
        picPath.append("/");
        dir.mkdir(picPath);
        dir.mkdir("contacts");
        dir.mkdir("digit");
        dir.mkdir("home");
        dir.mkdir("message");
    } else {
        //delayMS(1000);
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//
        picPath.append(QString("_%1/").arg(qrand()%10000));
        dir.setPath(picPath);
        if (!dir.exists()) {
            dir.mkdir(picPath);
            dir.mkdir("contacts");
            dir.mkdir("digit");
            dir.mkdir("home");
            dir.mkdir("message");
        }
    }
}

// 延时函数
void AdbSystemBase::delayMS(int ms)
{
#if 0 // 会阻塞线程
    // 这是阻塞的延时函数
    QTime _time = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < _time);
#endif
    // eventLoop 没有退出？？？
    QEventLoop loop1;
    QTimer::singleShot(ms, &loop1, SLOT(quit()));
    loop1.exec();
}

