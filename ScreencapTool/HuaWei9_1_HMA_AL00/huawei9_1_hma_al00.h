#ifndef HUAWEI9_1_HMA_AL00
#define HUAWEI9_1_HMA_AL00

#include "../screentool.h"
#include <QMap>
//#include "Log.h"

class HuaWei9_1_HMA_AL00:public ScreenTool
{
public:
    explicit HuaWei9_1_HMA_AL00();
    explicit HuaWei9_1_HMA_AL00(const QString& menufest, const QString &iSerial);
    ~HuaWei9_1_HMA_AL00();

    // 9.1为31个
      enum TaskListSystem9_1{ContactsList9_1=0, ContactsImpExp9_1, ContactsSetting9_1, ContactsGroup9_1, ContactsLinkedIn9_1, ContactsNew9_1,
                         DialDial9_1, DialMore9_1, DialDetail9_1, DialSave9_1, DialCollect9_1/*9.1特有*/,
                         HomeHome9_1, HomeFolder9_1, HomeWallpaper9_1/*9.1特有*/, HomeList9_1, HomeSetting9_1, HomeMenu9_1, HomeVolume9_1, HomeLock9_1,
                         MessageEmoticon9_1/*9.1特有*/, MessageList9_1, MessageWebsit9_1, MessageSetting9_1, MessageCentre9_1/*9.1特有*/, MessagePress9_1, MessageNew9_1,
                         MessageSearch9_1, MessageCollection9_1, MessageNotice9_1, MessageRailway9_1, MessageReports9_1};//31个


   // MyLog *log;
    QMap<int , void *> funList9_1;

    void  initFunList9_1();

    void taskIdSwitch(int i);

    void pushThemeToPhone(const QString &themeFile);

    //virtual void totalCutPicture(const QVector<int> &taskLists);
    // 主题安装
    virtual void themeInstall();
    // contact部分截图
//    virtual void contactCutImage();
//    // digit部分截图
//    virtual void digitCutImage();
//    // 桌面部分截图
//    virtual void homeCutImage();
//    // 短信部分截图
//    virtual void messageCutImage();

    virtual void contactsList();
    virtual void contactsImpExp();
    virtual void contactsSetting();
    virtual void contactsGroup();
    virtual void contactsLinkedIn();
    virtual void contactsNew();

    virtual void dialDial();
    virtual void dialMore();
    virtual void dialDetail();
    virtual void dialSave();
    /*9.1特有*/
    void dialCollect9_1();

    virtual void homeHome();
    virtual void homeFolder();
    virtual void homeList();
    virtual void homeSetting();
    virtual void homeMenu();
    virtual void homeLock();
    virtual void homeVolume();

    /*9.1特有*/
    void homeWallpaper9_1();
    void messageEmoticon9_1();
    void messageCentre9_1();


    virtual void messageList();
    virtual void messageWebsit();
    virtual void messageSetting();
    virtual void messagePress();
    virtual void messageNew();
    virtual void messageSearch();
    virtual void messageCollection();
    virtual void messageNotice();
    virtual void messageRailway();
    virtual void messageReports();

};

#endif // HUAWEI9_1_HMA_AL00
