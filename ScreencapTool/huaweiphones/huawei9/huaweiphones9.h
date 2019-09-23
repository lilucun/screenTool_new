#ifndef HUAWEIPHONES9_H
#define HUAWEIPHONES9_H

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


class HuaWeiPhones9 : public HuaWeiPhones
{
public:
    HuaWeiPhones9(const PhoneCharacters &phoneCharacters);

    // 9.1为31个
      enum TaskListSystem9_1{ContactsList9_1=0, ContactsImpExp9_1, ContactsSetting9_1, ContactsGroup9_1, ContactsLinkedIn9_1, ContactsNew9_1,
                         DialDial9_1, DialMore9_1, DialDetail9_1, DialSave9_1, DialCollect9_1/*9.1特有*/,
                         HomeHome9_1, HomeFolder9_1, HomeWallpaper9_1/*9.1特有*/, HomeList9_1, HomeSetting9_1, HomeMenu9_1, HomeVolume9_1, HomeLock9_1,
                         MessageEmoticon9_1/*9.1特有*/, MessageList9_1, MessageWebsit9_1, MessageSetting9_1, MessageCentre9_1/*9.1特有*/, MessagePress9_1, MessageNew9_1,
                         MessageSearch9_1, MessageCollection9_1, MessageNotice9_1, MessageRailway9_1, MessageReports9_1};//31个
      Pos mSearchPos;
      Pos getTextPozision(const QString&, const QByteArray &text);

      void init();
      void taskIdSwitch(int i)override;

      // 主题安装
      void themeInstall()override;

      void pushThemeToPhone(const QString &themeFile)override;
      void initPicPath()override;
      const QString getPicturePath()override;

    /**************
     * 华为手机共有的截图任务: 纯虚类子类必须实现，不然子类也是纯虚类
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

    void homeHome()override;
    void homeFolder()override;
    void homeList()override;
    void homeSetting()override;
    void homeMenu()override;
    void homeLock()override;
    void homeVolume()override;

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

    // 9.1特有
    void dialCollect9_1();
    void homeWallpaper9_1();
    void messageEmoticon9_1();
    void messageCentre9_1();
protected:

    // 键盘关闭
       short KEYBORDPOS_X;
       short KEYBORDPOS_Y;
       // 安装主题
       short MY_THEME_Y;// 字体坐标
       bool IS_CHECK_KEYBORD;
       short SINGAL_KB_SOP_Y;//add
       // 联系人清理
       bool IS_CLEAN_CALL = false;
       /*<!--联系人：  新建{电话输入 添加群组 添加更多} 群组 设置{设置 关于} 领英！导入导出{从其他设备导入 分享联系人{导入到卡1}}-->*/
       short C_NEW_CALL_Y;
       short C_NEW_ADDGROUP_Y;
       short C_NEW_ADDMORE_Y;
       short C_GROUP_Y;
       short C_SETTING_Y;
       short C_SETTING_ABOUT_Y;
       short C_LINKIN_Y;
       short C_IEMP_OTHERS_Y;
       short C_IEMP_TOSIM1_Y;
       /*<!-- dial：设置{更多 通话记录 } !-->*/
       short D_SETTING_Y;
       short D_SETTING_MORE_Y;// no use
       char D_SETTING_MORE_PAGE;//no use
       short D_SETTING_RECORD_Y;
       char D_SETTING_RECORD_PAGE;

       /*<!-- home：清理 锁屏页面 文件夹添加  !-->*/
       short H_CLEAN_PAGE_INDEX = 3;
       short H_CLOCK_PAGE_INDEX = 1;
       short H_FOLDER_ADD_X;
       short H_FOLDER_ADD_Y;

       /*<!-- message：设置更多{ 高级 短信中心} 长安短信{短信内容 短信上栏小的更多} !-->*/
       short M_SETTING_Y;
       short M_SETTING_GAOJI_Y;
       short M_SETTING_CENTRE_Y;
       short M_PRESS_MS_Y;
       short M_PRESS_LITTLE_Y;

       void initPosition();
       void test();
};

#endif // HUAWEIPHONES9_H
