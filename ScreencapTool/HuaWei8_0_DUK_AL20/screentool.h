#ifndef SCREENTOOL_H
#define SCREENTOOL_H

#include <QObject>
#include <QString>
#include <QMutex>
#include <QVector>
#include <QEventLoop>
#include <QApplication>


//Q_GLOBAL_STATIC(QString, IP_ADDR)

//const char IP_ADDR[] = "192.168.1.56";
//const char IP_ADDR[] = "192.168.1.56";// 服务器
//const char IP_ADDR[] = "10.4.41.158";// 梦薇
//const char IP_ADDR[] = "10.4.41.240";//http://192.168.1.56:8090
const char IP_ADDR[] = "10.4.37.96";// 有问题的
//#define IP_ADDR 10.4.43.67
const int PORT = 10001;
const int UPDATE_TIME = 4;//上报信息时间

struct ScreenSizeT
{
    int width;
    int height;
};


struct PhoneCharacters
{
    PhoneCharacters() {}
    QString phoneSerial;
    ScreenSizeT wm_size;
    QString phoneMenufest;
    QString phoneProduct;
    QString phoneVersion;
};

class ScreenTool:public QObject
{
    friend void cutImage(ScreenTool* tool, const QString & picDir,const QString & picName, int dalayMs);
    Q_OBJECT
public:

    explicit ScreenTool();
    explicit ScreenTool(const QString &menufest, const QString &serial);

    virtual ~ScreenTool();
    enum{devConn = 0x01, devDisConn = 0x02, devBusy = 0x03, devReady = 0x04, devAcceptTask = 0x05};

    void initPhone();

    int getPhoneStatues();
    void setPhoneStatues(int status);

    const QString getPhoneSerial();
    void setPhoneSerial(const QString& id);
    const QString getPhoneMenufest();
    const QString getPhoneProduct();
    void setPhoneProduct(const QString& product);
    const QString getPhoneVersion();
    void setPhoneVersion(const QString& version);
    const ScreenSizeT getPhoneSize();
    void setPhoneSize(const ScreenSizeT& size);
    const QString getPicturePath();

    virtual const QString pluginSerial();
    void initPhoneAliveTime();
    int getPhoneAliveTime();
    void phoneAliveTimePlusOne();

    void mkDirInitPicPath();
    void testFun();

protected:
    virtual void taskIdSwitch(int){}

    // 主题安装
    virtual void themeInstall(){}
    // contact部分截图
    virtual void contactCutImage(){}
    // digit部分截图
    virtual void digitCutImage(){}
    // 桌面部分截图
    virtual void homeCutImage(){}
    // 短信部分截图
    virtual void messageCutImage(){}
	
    virtual void pushThemeToPhone(const QString &){}
    /**************
     * 华为手机共有的截图任务
    ***************/
    virtual void contactsList(){}
    virtual void contactsImpExp(){}
    virtual void contactsSetting(){}
    virtual void contactsGroup(){}
    virtual void contactsLinkedIn(){}
    virtual void contactsNew(){}

    virtual void dialDial(){}
    virtual void dialMore(){}
    virtual void dialDetail(){}
    virtual void dialSave(){}

    virtual void homeHome(){}
    virtual void homeFolder(){}
    virtual void homeList(){}
    virtual void homeSetting(){}
    virtual void homeMenu(){}
    virtual void homeLock(){}
    virtual void homeVolume(){}

    virtual void messageList(){}
    virtual void messageWebsit(){}
    virtual void messageSetting(){}
    virtual void messagePress(){}
    virtual void messageNew(){}
    virtual void messageSearch(){}
    virtual void messageCollection(){}
    virtual void messageNotice(){}
    virtual void messageRailway(){}
    virtual void messageReports(){}


    // 8.0特有
    virtual void dialKeybord(){}
    virtual void dialMark(){}
    virtual void homeNetwork(){}
    virtual void homePower(){}
    virtual void homeSimpleMode(){}
    virtual void messageNavbar(){}
    virtual void messageSend(){}
    // 9.1特有
    virtual void dialCollect9_1(){}
    virtual void homeWallpaper9_1(){}
    virtual void messageEmoticon9_1(){}
    virtual void messageCentre9_1(){}

protected:
    QString adbStr;
    QString adbExe;
    //AdbProcess adbProcess;
    QEventLoop loop;//延时
    static QMutex mutex;

    int phoneStatues;
    QString picPath;
    QString timeTemp;
    int phoneAliveTime;// 60*60*8/n 8hours

    PhoneCharacters phoneCharacters;

    void initAdbStr();
    void clickScreen(int pox_x, int pox_y, int delay_ms);
    void clickScreenNoConverPos(int pox_x, int pox_y, int delay_ms);
    void cutAnImage(const QString &picDir, const QString &picName, int delay_ms);

    void startActivity(const QString& act_name);
     void restartActvity(const QString& appName);
    void swipeScreen(int begin_x, int begin_y, int end_x, int end_y, int delay_ms);
    void verticalRollToBottom();
    void verticalRollToTop();

    void expandNotifactionHalf();
    void expandNotifactionFull();
    void clickLongTime(int pox_x, int pox_y, int delay_ms);
    void clickLongTimeNoConverPos(int pox_x, int pox_y, int delay_ms);
    void returnHome();
    void addVolumes();
    void delVolumes();

    void collapseKeyboard();
    void swipeHalfCutImage(int begin_x, int begin_y, int end_x, int end_y,const QString & picDir,const QString & picName);
    void clickCancelCutImage(int pox_x, int pox_y, int delayMs,const QString & picDir,const QString & picName );


    void inputText(const QString & text);
    void delTextTens();
    void delTexts(int n);

    void commondAdbNoResults(const QString& commd);
    int commondAdbHasResults(const QString &commd, char *outResult);
    void commondAdbNoShell(const QString &commd);

    void delayMS(int ms);
    bool devIsDisConn(char *buf);

};

#endif // SCREENTOOL_H
