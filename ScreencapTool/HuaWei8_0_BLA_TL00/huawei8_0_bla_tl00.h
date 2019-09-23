#ifndef HUAWWU8_0_BLA_TL00
#define HUAWWU8_0_BLA_TL00

#include "../screentool.h"

class HuaWei8_0_BLA_TL00:public ScreenTool
{
public:
    HuaWei8_0_BLA_TL00();
    explicit HuaWei8_0_BLA_TL00(const QString& menufest, const QString &iSerial);
    // 任务场景 8.0为34
    enum TaskListSystem8_0{ContactsList=0, ContactsImpExp, ContactsSetting, ContactsGroup, ContactsLinkedIn, ContactsNew,
                           DialDial, DialKeybord/*8.0特有*/, DialMore, DialDetail, DialMark/*8.0特有*/, DialSave,
                           HomeHome, HomeFolder, HomeNetwork/*8.0特有*/, HomeList, HomeSetting, HomeMenu, HomeLock, HomePower/*8.0特有*/, HomeSimpleMode/*8.0特有*/, HomeVolume,
                           MessageList, MessageNavbar/*8.0特有*/, MessageSend/*8.0特有*/, MessageWebsit, MessageSetting, MessagePress, MessageNew, MessageSearch, MessageCollection, MessageNotice, MessageRailway, MessageReports};


    virtual void totalCutPicture(const QVector<int> &);
    virtual void taskIdSwitch(int i);
    // 主题安装
    virtual void themeInstall();
    // contact部分截图
    virtual void contactCutImage();
    // digit部分截图
    virtual void digitCutImage();
    // 桌面部分截图
    virtual void homeCutImage();
    // 短信部分截图
    virtual void messageCutImage();

    virtual void pushThemeToPhone(const QString &themeFile);

    /**************
     * 华为手机共有的截图任务
    ***************/
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
    // 特有
    void dialKeybord();
    void dialMark();

    virtual void homeHome();
    virtual void homeFolder();
    virtual void homeList();
    virtual void homeSetting();
    virtual void homeMenu();
    virtual void homeLock();
    virtual void homeVolume();

    void homeNetwork();
    void homePower();
    void homeSimpleMode();

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

    void messageNavbar();
    void messageSend();
};

#endif // HuaWei8_0_BLA_AL00
