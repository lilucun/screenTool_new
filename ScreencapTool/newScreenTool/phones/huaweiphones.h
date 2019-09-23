#ifndef HUAWEIPHONES_H
#define HUAWEIPHONES_H

#include "phones.h"
#include "../adb/adbsystemhuawei.h"
//#include <QPointer>

class HuaWeiPhones : public Phones
{
public:
//    HuaWeiPhones();
    HuaWeiPhones(const PhoneCharacters &phoneCharacters);

    /**************
     * 华为手机共有的截图任务: 纯虚类子类必须实现，不然子类也是纯虚类
    ***************/
    virtual void contactsList()=0;
    virtual void contactsImpExp()=0;
    virtual void contactsSetting()=0;
    virtual void contactsGroup()=0;
    virtual void contactsLinkedIn()=0;
    virtual void contactsNew()=0;

    virtual void dialDial()=0;
    virtual void dialMore()=0;
    virtual void dialDetail()=0;
    virtual void dialSave()=0;

    virtual void homeHome()=0;
    virtual void homeFolder()=0;
    virtual void homeList()=0;
    virtual void homeSetting()=0;
    virtual void homeMenu()=0;
    virtual void homeLock()=0;
    virtual void homeVolume()=0;

    virtual void messageList()=0;
    virtual void messageWebsit()=0;
    virtual void messageSetting()=0;
    virtual void messagePress()=0;
    virtual void messageNew()=0;
    virtual void messageSearch()=0;
    virtual void messageCollection()=0;
    virtual void messageNotice()=0;
    virtual void messageRailway()=0;
    virtual void messageReports()=0;

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
    AdbSystemHuaWei *adbSystem;

};

#endif // HUAWEIPHONES_H
