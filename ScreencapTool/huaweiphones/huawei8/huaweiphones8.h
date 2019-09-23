#ifndef HUAWEIPHONES8_H
#define HUAWEIPHONES8_H

#include "../../newScreenTool/phones/huaweiphones.h"


struct Pos
{
    Pos(int x=0, int y=0) {
        pos_x = x;
        pos_y = y;
    }
    int pos_x;
    int pos_y;
};

class HuaWeiPhones8 : public HuaWeiPhones
{
public:
    HuaWeiPhones8(const PhoneCharacters &phoneCharacters);
    // 任务场景 8.0为34
    enum TaskListSystem8_0{ContactsList=0, ContactsImpExp, ContactsSetting, ContactsGroup, ContactsLinkedIn, ContactsNew,
                           DialDial, DialKeybord/*8.0特有*/, DialMore, DialDetail, DialMark/*8.0特有*/, DialSave,
                           HomeHome, HomeFolder, HomeNetwork/*8.0特有*/, HomeList, HomeSetting, HomeMenu, HomeLock, HomePower/*8.0特有*/, HomeSimpleMode/*8.0特有*/, HomeVolume,
                           MessageList, MessageNavbar/*8.0特有*/, MessageSend/*8.0特有*/, MessageWebsit, MessageSetting, MessagePress, MessageNew, MessageSearch, MessageCollection, MessageNotice, MessageRailway, MessageReports};

    Pos mSearchPos;
    Pos getTextPozision(const QString&, const QByteArray &text);

    void taskIdSwitch(int i)override;

    // 主题安装
    void themeInstall()override;

    void pushThemeToPhone(const QString &themeFile)override;
    void initPicPath()override;
    const QString getPicturePath()override;

    void recoverEnv();
    bool keyBoardIsDown(const QString &img);
    /**************
     * 华为手机共有的截图任务
    ***************/
    void contactsList()override;
    void contactsImpExp()override;
    void contactsSetting()override;
    void contactsGroup()override;
    void contactsLinkedIn()override;
    void contactsNew()override;

    void dialDial()override;
    void dialMore()override;
    void dialDetail()override;
    void dialSave()override;
    // 特有
    void dialKeybord()override;
    void dialMark()override;

    void homeHome()override;
    void homeFolder()override;
    void homeList()override;
    void homeSetting()override;
    void homeMenu()override;
    void homeLock()override;
    void homeVolume()override;

    void homeNetwork()override;
    void homePower()override;
    void homeSimpleMode()override;

    void messageList()override;
    void messageWebsit()override;
    void messageSetting()override;
    void messagePress()override;
    void messageNew()override;
    void messageSearch()override;
    void messageCollection()override;
    void messageNotice()override;
    void messageRailway()override;
    void messageReports()override;

    void messageNavbar()override;
    void messageSend()override;
    void init();

protected:
    // 键盘关闭
       short KEYBORDPOS_X;
       short KEYBORDPOS_Y;
       //
       bool IS_CHECK_KEYBORD;
       short SINGAL_KB_SOP_Y;//add
       /*<!--联系人：  新建{电话输入 添加群组 添加更多} 群组 设置关于 领英！导入导出{从其他设备导入 分享联系人{导入到卡1}}-->*/
       short C_NEW_CALL_Y;
       short C_NEW_ADDGROUP_Y;
       short C_NEW_ADDMORE_Y;
       short C_GROUP_Y;
       short C_SETTING_ABOUT_Y;
       short C_LINKIN_Y;
       short C_IEMP_OTHERS_Y;
       short C_IEMP_TOSIM1_Y;
       /*<!-- dial：设置{更多 通话记录 来电拒绝[页码]} !-->*/
       short D_SETTING_MORE_Y;// no use
       char D_SETTING_MORE_PAGE;//no use
       short D_SETTING_RECORD_Y;
       char D_SETTING_RECORD_PAGE;
       short D_SETTING_REJECT_Y;
       char D_SETTING_REJECT_PAGE;
       /*<!-- home：文件夹添加 设置{search} !-->*/
       short H_FOLDER_ADD_X;
       short H_FOLDER_ADD_Y;
       short H_SETTING_SEARCH_Y;//change
       /*<!-- message：设置更多{智能短信服务 高级 常用短语 签名 短信中心} 长安短信{短信上栏小的更多} !-->*/
       short M_SETTING_SERVICES_Y;
       short M_SETTING_GAOJI_Y;
       short M_SETTING_OFTEN_Y;
       short M_SETTING_MARK_Y;
       short M_SETTING_CENTRE_Y;
       short M_PRESS_LITTLE_Y;
       QString ocrToken;
       void test();

       void initPosition();
};

#endif // HUAWEIPHONES8_H
