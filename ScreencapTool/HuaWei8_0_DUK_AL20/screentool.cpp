#include "screentool.h"
#include <QProcess>
#include <QDebug>
#include <QRegularExpression>
#include <QCoreApplication>
#include <QTime>
#include <QDir>
#include <QMutexLocker>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>


QMutex ScreenTool::mutex;


void ScreenTool::testFun()
{
    qDebug() << this->phoneCharacters.phoneVersion;

    qDebug() << this->picPath;
}


ScreenTool::ScreenTool()
{

}

ScreenTool::ScreenTool(const QString &menufest, const QString &serial)
{

    phoneStatues = ScreenTool::devConn;

    this->phoneCharacters.phoneSerial = serial;
    this->phoneCharacters.phoneMenufest = menufest;
    initPhone();
}



ScreenTool::~ScreenTool()
{
    qDebug() << "delete screen";
}

void ScreenTool::initPhone()
{
    initAdbStr();
    initPhoneAliveTime();

    phoneStatues = ScreenTool::devReady;
}

int ScreenTool::getPhoneStatues()
{
    return (int)this->phoneStatues;
}

void ScreenTool::setPhoneStatues(int status)
{
    this->phoneStatues = status;
}

const QString ScreenTool::getPhoneSerial()
{
    return this->phoneCharacters.phoneSerial;
}

void ScreenTool::setPhoneSerial(const QString &id)
{
    this->phoneCharacters.phoneSerial = id;
}

const QString ScreenTool::getPhoneMenufest()
{
    return this->phoneCharacters.phoneMenufest;
}

const QString ScreenTool::getPhoneProduct()
{
    return this->phoneCharacters.phoneProduct;
}

void ScreenTool::setPhoneProduct(const QString &product)
{
    this->phoneCharacters.phoneProduct = product;
}

const QString ScreenTool::getPhoneVersion()
{
    return this->phoneCharacters.phoneVersion;
}

void ScreenTool::setPhoneVersion(const QString &version)
{
    this->phoneCharacters.phoneVersion = version;
}

const ScreenSizeT ScreenTool::getPhoneSize()
{
    return this->phoneCharacters.wm_size;
}

void ScreenTool::setPhoneSize(const ScreenSizeT &size)
{
    this->phoneCharacters.wm_size.height = size.height;
    this->phoneCharacters.wm_size.width = size.width;
}

const QString ScreenTool::getPicturePath()
{
    return this->picPath;
}

const QString ScreenTool::pluginSerial()
{
    return QString("");
}

void ScreenTool::initPhoneAliveTime()
{
    phoneAliveTime = 60 / UPDATE_TIME;
}

int ScreenTool::getPhoneAliveTime()
{
    return phoneAliveTime;
}

void ScreenTool::phoneAliveTimePlusOne()
{
    phoneAliveTime--;
}



#if 1
void ScreenTool::mkDirInitPicPath()
{
    // 加锁，减少冲突
    QMutexLocker lock(&mutex);

    if (!picPath.isEmpty())
        picPath.clear();
    // get exe dir 目录不能有空格等非标准命名
    picPath.append(QCoreApplication::applicationDirPath());
    // get time
#if 1
    picPath.append("/temp");
    QDir dir(picPath);
    if(!dir.exists())
        dir.mkdir(picPath);
    picPath.append("/");

    QDateTime currenTime = QDateTime::currentDateTime();
    timeTemp = currenTime.toString("yyyy_MM_dd_hh_mm_ss");
    picPath.append(timeTemp);

    dir.setPath(picPath);
#else
    picPath.append("/");

    QDateTime currenTime = QDateTime::currentDateTime();
    timeTemp = currenTime.toString("yyyy_MM_dd_hh_mm_ss");
    picPath.append(timeTemp);
    QDir dir(picPath);
#endif
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
#endif


void ScreenTool::initAdbStr()
{
    adbExe = QApplication::applicationDirPath();
    adbExe.append("/plugins/adb/adb.exe");

    adbStr.clear();
    adbStr.append(adbExe);
    adbStr.append(" -s ");
    adbStr.append(getPhoneSerial());
    adbStr.append(" shell ");
}

void ScreenTool::clickScreen(int pox_x, int pox_y, int delay_ms)
{
    // 坐标转换
    //nx = int(120 / 1080.0 * int(dw));
    //ny = int(200 / 320.0 * int(dh));
    int _pox_x = (pox_x/ 1080.0) * phoneCharacters.wm_size.width;
    int _pox_y = (pox_y/ 2160.0) * phoneCharacters.wm_size.height;

    commondAdbNoResults(QString("input tap %1 %2").arg(_pox_x).arg(_pox_y));
  
    delayMS(delay_ms);

}

/* 按原始坐标点击屏幕
*/
void ScreenTool::clickScreenNoConverPos(int pox_x, int pox_y, int delay_ms)
{
    commondAdbNoResults(QString("input tap %1 %2").arg(pox_x).arg(pox_y));

    delayMS(delay_ms);
}

void ScreenTool::cutAnImage(const QString &picDir, const QString &picName, int delay_ms)
{
    Q_UNUSED(delay_ms);
    if (picPath.size() == 0) {
        qCritical("图片路径为null，截图失败！！！");
        return;
    }

 #if 0
    QProcess pro;
    pro.start("cmd",  QStringList() <<"/c" << QString("%1 screencap -p > %2.png").arg(adbStr).arg(timeTemp));
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



void ScreenTool::startActivity(const QString & act_name)
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
void ScreenTool::swipeScreen(int begin_x, int begin_y, int end_x, int end_y, int delay_ms)
{
    int _begin_x = (begin_x/ 1080.0 * phoneCharacters.wm_size.width);
    int _begin_y = (begin_y/ 2160.0 * phoneCharacters.wm_size.height);
    int _end_x = (end_x/ 1080.0 * phoneCharacters.wm_size.width);
    int _end_y = (end_y/ 2160.0 * phoneCharacters.wm_size.height);

    commondAdbNoResults(QString("input swipe %1 %2 %3 %4").arg(_begin_x).arg(_begin_y).arg(_end_x).arg(_end_y));

    delayMS(delay_ms);

}
/* 选中页面最底部的item(滑动到最底部)
 */
void ScreenTool::verticalRollToBottom()
{
    commondAdbNoResults("input roll 0 1000");
    delayMS(500);
}

/* 选中页面最顶部的item(滑动到最顶部)
 */
void ScreenTool::verticalRollToTop()
{
    commondAdbNoResults("input roll 0 -1000");
    delayMS(500);
}



void ScreenTool::restartActvity(const QString &appName)
{
    if(appName.size() == 0)
        return;
    // 参数-S可以先关闭 app 再启动activity
    commondAdbNoResults(QString("am start -S %1").arg(appName));

    delayMS(500);

}
/* 部分展开通知栏
*/
void ScreenTool::expandNotifactionHalf()
{
    commondAdbNoResults("cmd statusbar expand-notifications");
    delayMS(500);
}
/* 全部展开通知栏
*/
void ScreenTool::expandNotifactionFull()
{
    commondAdbNoResults("cmd statusbar expand-settings");
    delayMS(500);
}


void ScreenTool::clickLongTime(int pox_x, int pox_y, int delay_ms)
{
    int _pox_x = (pox_x/ 1080.0 * phoneCharacters.wm_size.width);
    int _pox_y = (pox_y/ 2160.0 * phoneCharacters.wm_size.height);

    commondAdbNoResults(QString("input swipe %1 %2 %3 %4 %5").arg(_pox_x).arg(_pox_y).arg(_pox_x+1).arg(_pox_y+1).arg(delay_ms));

    delayMS(200);
}

void ScreenTool::clickLongTimeNoConverPos(int pox_x, int pox_y, int delay_ms)
{
    commondAdbNoResults(QString("input swipe %1 %2 %3 %4 %5").arg(pox_x).arg(pox_y).arg(pox_x+1).arg(pox_y+1).arg(delay_ms));

    delayMS(200);
}

void ScreenTool::returnHome()
{
    commondAdbNoResults("input keyevent 3");

    delayMS(500);
}

void ScreenTool::addVolumes()
{
    commondAdbNoResults("input keyevent 24");

    delayMS(500);

}
// 音量减
void ScreenTool::delVolumes()
{
    commondAdbNoResults("input keyevent 25");

    delayMS(100);
}
/* 收起输入的软键盘
*/
void ScreenTool::collapseKeyboard()
{
    commondAdbNoResults("input keyevent 111");

    delayMS(400);
}

void cutImage(ScreenTool* tool, const QString & picDir,const QString & picName, int dalayMs)
{
    QTime _time = QTime::currentTime().addMSecs(dalayMs);// 1s
    while (QTime::currentTime() < _time) {}
    tool->cutAnImage(picDir, picName, 10);
}

void ScreenTool::swipeHalfCutImage(int begin_x, int begin_y, int end_x, int end_y,const QString & picDir,const QString & picName)
{
    int _begin_x = (begin_x/ 1080.0 * phoneCharacters.wm_size.width);
    int _begin_y = (begin_y/ 2160.0 * phoneCharacters.wm_size.height);
    int _end_x = (end_x/ 1080.0 * phoneCharacters.wm_size.width);
    int _end_y = (end_y/ 2160.0 * phoneCharacters.wm_size.height);

    QtConcurrent::run(cutImage, this, picDir, picName, 1900);
    commondAdbNoResults(QString("input swipe %1 %2 %3 %4 3000").arg(_begin_x).arg(_begin_y).arg(_end_x).arg(_end_y));
    // 截取图片

}

void ScreenTool::clickCancelCutImage(int pox_x, int pox_y, int delayMs, const QString &picDir, const QString &picName)
{
//    int _pox_x = (pox_x/ 1080.0 * phoneCharacters.wm_size.width);
//    int _pox_y = (pox_y/ 2160.0 * phoneCharacters.wm_size.height);

    QtConcurrent::run(cutImage, this, picDir, picName, 1800);
    clickLongTime(pox_x, pox_y, delayMs);
}

// 在输入框上输入内容
void ScreenTool::inputText(const QString &text)
{
    commondAdbNoResults(QString("input text %1").arg(text));

    delayMS(500);
}

void ScreenTool::delTextTens()
{
    delTexts(10);
}

void ScreenTool::delTexts(int n)
{
    for(int i = 0; i < n; ++i)
        commondAdbNoResults(QString("input keyevent 67"));
}



void ScreenTool::commondAdbNoResults(const QString &commd)
{
    // 判断 adbStr 是否为null
    if (adbStr.size() == 0)
        qCritical() << "adb 前缀未初始化";


    QString temp(adbStr);
    temp.append(commd);

//    qDebug() << temp;

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

int ScreenTool::commondAdbHasResults(const QString&  commd, char *outResult)
{
    //
    if(outResult == NULL || adbStr.size() == 0)
        return -1;

    QString temp(adbStr);
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

void ScreenTool::commondAdbNoShell(const QString &commd)
{
    // 判断 adbStr 是否为null
    QString temp(adbExe);
    temp.append(" -s ");
    temp.append(this->getPhoneSerial());
    temp.append("  ");
    temp.append(commd);

    qDebug() << temp;

    QProcess pro;
    pro.execute(temp);
    //system(temp.toStdString().c_str());

}

bool ScreenTool::devIsDisConn(char *buf)
{
    if(buf == NULL)
        return false;

    QRegularExpression reg("^error: device \'.+\' not found");
    return (QString(buf).contains(reg));
}

// 延时函数
void ScreenTool::delayMS(int ms)
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

