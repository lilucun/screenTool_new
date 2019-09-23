#include "huawei9_1_ele_al00.h"

HuaWei9_1_ELE_AL00::HuaWei9_1_ELE_AL00()
{

}

HuaWei9_1_ELE_AL00::HuaWei9_1_ELE_AL00(const QString &menufest, const QString &iSerial):ScreenTool(menufest, iSerial)
{
    //initFunList9_1();
    //log = new MyLog("HuaWei9_1_ELE_AL00.txt");
}

HuaWei9_1_ELE_AL00::~HuaWei9_1_ELE_AL00()
{
    //delete log;
}
// 初始化函数map
void HuaWei9_1_ELE_AL00::initFunList9_1()
{
    //contactsGroup;
    //funList9_1.insert(ContactsGroup9_1, (void*)contactsGroup);

}

void HuaWei9_1_ELE_AL00::taskIdSwitch(int i)
{
    switch (i) {
    case ContactsList9_1:
        contactsList();
        break;
    case ContactsImpExp9_1:
        contactsImpExp();
        break;
    case ContactsSetting9_1:
        contactsSetting();
        break;
    case ContactsGroup9_1:
        contactsGroup();
        break;
    case ContactsLinkedIn9_1:
        contactsLinkedIn();
        break;
    case ContactsNew9_1:
        contactsNew();
        break;

    case DialDial9_1:
        dialDial();
        break;
    case DialMore9_1:
        dialMore();
        break;
    case DialDetail9_1:
        dialDetail();
        break;
    case DialSave9_1:
        dialSave();
        break;
    case DialCollect9_1:
        dialCollect9_1();
        break;

    case HomeHome9_1:
        homeHome();
        break;
    case HomeFolder9_1:
        homeFolder();
        break;

    case HomeList9_1:
        homeList();
        break;
    case HomeSetting9_1:
        homeSetting();
        break;
    case HomeMenu9_1:
        homeMenu();
        break;
    case HomeLock9_1:
        homeLock();
        break;
    case HomeVolume9_1:
        homeVolume();
        break;
    case HomeWallpaper9_1:
        homeWallpaper9_1();
        break;

    case MessageList9_1:
        messageList();
        break;

    case MessageWebsit9_1:
        messageWebsit();
        break;
    case MessageSetting9_1:
        messageSetting();
        break;
    case MessagePress9_1:
        messagePress();
        break;
    case MessageNew9_1:
        messageNew();
        break;
    case MessageSearch9_1:
        messageSearch();
        break;
    case MessageCollection9_1:
        messageCollection();
        break;
    case MessageNotice9_1:
        messageNotice();
        break;
    case MessageRailway9_1:
        messageRailway();
        break;
    case MessageReports9_1:
        messageReports();
        break;
    case MessageCentre9_1:
        messageCentre9_1();
        break;
    case MessageEmoticon9_1:
        messageEmoticon9_1();
        break;

    default:
        break;
    }
}


void HuaWei9_1_ELE_AL00::pushThemeToPhone(const QString &themeFile)
{
    // 删除旧的themes
    QString str;
    str.append("rm /sdcard/HuaWei/Themes/*.hwt");

    //adbProcess.execAdbCommod(str);
    commondAdbNoResults(str);

    delayMS(100);

    str.clear();
    str.append(QString("push "));
    str.append(themeFile);
    str.append(" /sdcard/HuaWei/Themes/");

    //adbProcess.execAdbCommod(str);
    commondAdbNoShell(str);
}


void HuaWei9_1_ELE_AL00::themeInstall()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启主题
    restartActvity("com.huawei.android.thememanager/.HwThemeManagerActivity");
    // 我的
    clickScreen(927, 2188, 800);
    // 我的主题
    clickScreen(297, 933, 1000);
    //
    clickScreen(206, 624, 1000);
    // 279 1990 更新取消
    clickScreen(279, 2102, 500);
    // 应用
    clickScreen(491, 2155,3000);
    // 279 1990 更新取消
    clickScreen(279, 2102, 500);
    // 不保留 锁屏杂志
    clickScreen(269, 2121, 3000);
    // home
    returnHome();
}

void HuaWei9_1_ELE_AL00::contactCutImage()
{
    contactsList();
    contactsImpExp();
    contactsSetting();
    contactsGroup();
    contactsLinkedIn();
    contactsNew();
}

void HuaWei9_1_ELE_AL00::digitCutImage()
{
    dialDial();
    dialMore();
    dialDetail();
    dialSave();
    dialCollect9_1();
}

void HuaWei9_1_ELE_AL00::homeCutImage()
{
    homeHome();
    homeFolder();
    homeList();
    homeSetting();
    homeMenu();
    homeLock();
    homeVolume();
    homeWallpaper9_1();
}

void HuaWei9_1_ELE_AL00::messageCutImage()
{
    messageList();
    messageWebsit();
    messageSetting();
    messagePress();
    messageNew();
    messageSearch();
    messageCollection();
    messageNotice();
    messageRailway();
    messageReports();
    messageCentre9_1();
    messageEmoticon9_1();
}

/********************************************************************/
// 联系人列表
void HuaWei9_1_ELE_AL00::contactsList()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    clickScreen(541, 2176, 500);

    // 截图
    cutAnImage("contacts", "联系人列表-1.png", 100);
    // 滑动屏幕
    swipeScreen(571, 1567, 571, 600, 500);
    // 下滑
    swipeScreen(686, 534, 686, 834, 800);
    // 截图
    cutAnImage("contacts", "联系人列表-2.png", 100);

    // 点击联系人
    clickScreen(541, 2176, 500);
    // 固定联系人
    clickScreen(443, 1966, 500);
    // 点击
    // 截图
    cutAnImage("contacts", "联系人列表-3.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::contactsImpExp()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    clickScreen(541, 2176, 500);

    // 点击...
    clickScreen(1001, 171, 500);
    // 点击设置
    clickScreen(758, 431, 500);
    // 点击导入导出
    clickScreen(283, 1005, 500);
    // 截图
    cutAnImage("contacts", "导入导出-1.png", 100);
    // 通过蓝牙导入联系人
    clickScreen(301, 448, 500);
    // 截图
    cutAnImage("contacts", "导入导出-2.png", 100);
    // 返回
    clickScreen(78, 154, 500);
    // 点击从卡1导入
    clickScreen(184, 790, 500);
    // 点击全选
    clickScreen(666, 2148, 500);
    // 点击导入
    clickScreen(408, 2148, 500);
    // 截图
    cutAnImage("contacts", "导入导出-3.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::contactsSetting()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    clickScreen(541, 2176, 500);
    // 点击...
    clickScreen(1001, 171, 500);
    // 点击设置
    clickScreen(758, 431, 500);
    // 点击关于
    clickScreen(171, 1803, 500);
    // 截图
    cutAnImage("contacts", "设置-关于.png", 100);
    // 调出导航栏
    swipeScreen(782, 2217, 782, 1789, 800);
    // 截图
    cutAnImage("contacts", "设置-关于-1.png", 100);
    // 关闭导航栏
    clickScreen(139, 2182, 500);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::contactsGroup()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    clickScreen(541, 2176, 500);
    // 点击群组
    clickScreen(343, 478, 500);
    // 截图
    cutAnImage("contacts", "群组-群组.png", 100);
    // 点击新建
    clickScreen(410, 2188, 500);
    // 截图
    cutAnImage("contacts", "群组-新建.png", 100);
    // 输入666
    clickScreen(53, 2119, 500);
    clickScreen(600, 1586, 100);
    clickScreen(600, 1586, 100);
    clickScreen(600, 1586, 500);
    // 截图
    cutAnImage("contacts", "群组-新建-1.png", 100);
    // 返回home
    returnHome();

}

void HuaWei9_1_ELE_AL00::contactsLinkedIn()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    clickScreen(541, 2176, 500);
    // 点击领英
    clickScreen(334, 862, 500);
    // 截图
    cutAnImage("contacts", "领英.png", 100);
    // 返回home
    returnHome();

}

void HuaWei9_1_ELE_AL00::contactsNew()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    clickScreen(541, 2176, 500);
    // 点击新建
    clickScreen(919, 1963, 500);
    // 截图
    cutAnImage("contacts", "新建-新建联系人.png", 100);

    // 返回home
    returnHome();
}

/******************************************************8888888888888888888888888**********/

void HuaWei9_1_ELE_AL00::dialDial()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击电话
    clickScreen(177, 2166, 500);
    // 截图
    cutAnImage("digit","拨号盘-1.png", 100);
    // 关闭键盘
    clickScreen(115, 1960, 500);
    //下滑
    swipeScreen(700, 445, 700, 745, 800);

    // 截图
    cutAnImage("digit","拨号盘-2.png", 100);
    // 上滑动
    swipeScreen(746, 1069, 746, 700, 800);
    // 截图
    cutAnImage("digit","拨号盘-3.png", 100);
    // 打开键盘
    clickScreen(926, 1973, 500);
    // 输入151
    clickScreen(220, 1203, 100);
    clickScreen(526, 1398, 100);
    clickScreen(220, 1203, 500);
    // 截图
    cutAnImage("digit","拨号盘-4.png", 100);
    // 输入1511
    clickScreen(220, 1203, 100);
    clickScreen(526, 1398, 100);
    clickScreen(220, 1203, 100);
    clickScreen(220, 1203, 500);
    // 截图
    cutAnImage("digit","拨号盘-5.png", 100);
    /*******/
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::dialMore()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击电话
    clickScreen(177, 2166, 500);
    // 点击...
    clickScreen(994, 187, 500);
    // 截图
    cutAnImage("digit", "更多设置-更多.png", 100);
    // 设置
    clickScreen(764, 879, 500);
    // 自动通话录音
    clickScreen(244, 684, 500);
    // 截图
    cutAnImage("digit", "更多设置-通话自动录音.png", 100);

    // 指定号码
    clickScreen(155, 641, 500);
    // 截图
    cutAnImage("digit", "更多设置-通话自动录音-1.png", 100);

    /*******/
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::dialDetail()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击电话
    clickScreen(177, 2166, 500);
    // 点击 !
    clickScreen(999, 470, 500);
    // 截图
    cutAnImage("digit", "详情-联系人详情.png", 100);

    // 点击 ...
    clickScreen(800, 2155, 500);
    // 点击 标记为
    clickScreen(771, 1845, 500);
    // 标记
    clickScreen(555, 800, 500);
    // 点击 ...
    clickScreen(800, 2155, 500);
    // 点击 标记为
    clickScreen(771, 1845, 500);
    // 截图
    cutAnImage("digit", "详情-联系人详情标记.png", 100);


    /*******/
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::dialSave()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击电话
    clickScreen(177, 2166, 500);
    // 长按号码
    clickLongTime(362, 291, 1000);
    // 截图
    cutAnImage("digit", "长按保存.png", 100);
    // 保存至已有联系人
    clickScreen(604, 805, 500);
    // 截图
    cutAnImage("digit", "长按保存-保存至已有联系人.png", 100);
    /*******/
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::dialCollect9_1()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击收藏编辑
    clickScreen(900, 2166, 500);
//    // 点击...
//    clickScreen(991, 155, 500);
//    // 设置
//    clickScreen(762, 286, 500);
    // 长按
    clickLongTime(555, 600, 1000);
    // 截图
    cutAnImage("digit", "收藏编辑.png", 100);

    /*******/
    // 返回home
    returnHome();
}


/****************************************************************************************************/

void HuaWei9_1_ELE_AL00::homeHome()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 左滑
    swipeScreen(239, 1704, 470, 1704, 500);
    // 截屏
    cutAnImage("home","桌面-1.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::homeFolder()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 右滑
    swipeScreen(906, 1375, 252, 1375, 500);
    // 文件夹2、
    clickScreen(961, 234, 500);
    //截屏
    cutAnImage("home","文件夹-4.png", 100);
    // 左边滑动
    swipeScreen(858, 1154, 255, 1154, 500);
    // +
    clickScreen(296, 1244, 500);
    // 截屏
    cutAnImage("home","文件夹添加.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::homeList()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 应用程序
    clickScreen(553, 2083, 500);
    // 截图
    cutAnImage("home","应用列表-1.png", 100);
    // 点击s
    clickScreen(1053, 1620, 1500);
    // 截图
    cutAnImage("home","应用列表-6.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::homeSetting()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 长按
    clickLongTime(553, 1299, 1000);
    // 桌面设置
    clickScreen(913, 1898, 500);
    // 截图
    cutAnImage("home","桌面设置.png", 100);
    // 返回home
    returnHome();
}


void HuaWei9_1_ELE_AL00::homeMenu()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 下拉
    swipeScreen(671, 21, 690, 1628, 500);
    // 展开图标
    swipeScreen(544, 630, 576, 1223, 500);
    // 截图
    cutAnImage("home","桌面下拉.png", 100);
    // 编辑
    clickScreen(814, 187, 500);
    // 截图
    cutAnImage("home","桌面下拉-编辑.png", 100);
    // 返回home
    returnHome();}

void HuaWei9_1_ELE_AL00::homeLock()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 长按
    clickLongTime(553, 1299, 1000);
    // 窗口小工具
    clickScreen(419, 1866, 500);
    // 左边滑动3次
    swipeScreen(741, 2083, 300, 2083, 500);
    swipeScreen(741, 2083, 300, 2083, 500);
    swipeScreen(741, 2083, 300, 2083, 500);
    // 截图
    cutAnImage("home","一键优化.png", 100);
    // 左边滑动2次
    swipeScreen(741, 2083, 300, 2083, 500);
    swipeScreen(741, 2083, 300, 2083, 500);
    swipeScreen(741, 2083, 300, 2083, 500);
    // 截图
    cutAnImage("home","一件锁屏.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::homeVolume()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 按下
    addVolumes();
    // 截图
    cutAnImage("home","音量.png", 100);
    // 返回home
    returnHome();}

void HuaWei9_1_ELE_AL00::homeWallpaper9_1()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 长按
    clickLongTime(553, 1299, 1000);
    // 壁纸
    clickScreen(171, 1925, 1500);
    // 图片
    clickScreen(869, 548, 1000);
    //670 2154
    clickScreen(670, 2154, 500);
    // 截图
    cutAnImage("home","桌面壁纸.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageEmoticon9_1()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索输入18500
    this->clickScreen(374, 322, 800);
    this->clickScreen(70, 2061, 100);
    this->clickScreen(42, 1580, 100);
    this->clickScreen(816, 1580, 100);
    this->clickScreen(492, 1580, 100);
    this->clickScreen(1008, 1580, 100);
    this->clickScreen(1008, 1580, 800);
    // 点击短信
    this->clickScreen(482, 425, 500);
    // 点击表情
    this->clickScreen(867, 2171, 500);
    // 点击三角形
    this->clickScreen(859, 2198, 500);
    // 截图
    cutAnImage("message", "表情符号-0.png", 100);
    // 点击表情
    clickScreen(241, 2195, 500);
    // 截图
    cutAnImage("message", "表情符号-1.png", 100);
    // 返回home
    returnHome();

}

void HuaWei9_1_ELE_AL00::messageCentre9_1()
{ // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // 点击...
    this->clickScreen(1018, 155, 500);
    // 点击设置
     this->clickScreen(744, 863, 500);
    // 高级
    this->clickScreen(306, 1292, 500);
    // 卡2 短信中心
    this->clickScreen(303, 1056, 500);
    // 截图
    cutAnImage("message", "短信中心.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageList()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    /*******/
    // 截图1
     cutAnImage("message", "短信列表-1.png", 100);
    // 截图2
     //cutAnImage("message", "短信列表-2.png", 100);
    // 长按短信
    clickLongTime(701, 871, 1000);
    // 截图
     cutAnImage("message", "短信列表-3.png", 100);
    /*******/
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageWebsit()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索输入18630
    this->clickScreen(374, 322, 800);
    this->clickScreen(70, 2061, 100);
    this->clickScreen(42, 1580, 100);
    this->clickScreen(816, 1580, 100);

    this->clickScreen(591, 1580, 100);
    this->clickScreen(268, 1580, 100);
    this->clickScreen(1008, 1580, 800);
    // 点击短信
    this->clickScreen(482, 425,500);
    // 截图
    cutAnImage("message", "恶意网址.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageSetting()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // 点击...
    this->clickScreen(1018, 155, 500);
    // 截图
    cutAnImage("message", "设置-更多.png", 100);
    // 点击拦截骚扰
    this->clickScreen(779, 583, 500);
    // 点击 拦截规则
    clickScreen(799, 2163, 800);
    // 截图
    cutAnImage("message", "设置-设置.png", 100);
    // 返回home
    returnHome();

}

void HuaWei9_1_ELE_AL00::messagePress()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");

    // 搜索输入18500
    this->clickScreen(374, 322, 700);
    this->clickScreen(70, 2061, 100);
    this->clickScreen(42, 1580, 100);
    this->clickScreen(816, 1531, 100);
    this->clickScreen(492, 1570, 100);
    this->clickScreen(1008, 1572, 100);
    this->clickScreen(1008, 1572, 800);
    // 点击短信
    this->clickScreen(482, 425, 500);
    // 长按
    clickLongTime(752, 1369, 1000);
    // 截图
    cutAnImage("message", "长按短信-1.png", 100);
    // 小的更多
    clickScreen(954, 1268, 500);
    // 截图
    cutAnImage("message", "长按短信-2.png", 100);
    // 大的更多
    clickScreen(967, 2153, 500);
    // 截图
    cutAnImage("message", "长按短信-3.png", 100);
    // 查看详情
    clickScreen(800, 1829, 500);
    // 截图
    cutAnImage("message", "长按短信-4.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageNew()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // +
    clickScreen(948, 2131, 500);

    // 输入 151 2213 9813
    clickScreen(241, 308, 600);
    this->clickScreen(70, 2061, 100);
    this->clickScreen(42, 1580, 100);
    this->clickScreen(480, 1571, 500);
    // 截图
    cutAnImage("message", "新建-1.png", 100);
    this->clickScreen(42, 1580, 100);
    this->clickScreen(169, 1580, 100);
    this->clickScreen(169, 1580, 100);
    this->clickScreen(42, 1580, 100);
    this->clickScreen(271, 1570, 100);
    this->clickScreen(913, 1572, 100);
    this->clickScreen(816, 1572, 100);
    this->clickScreen(42, 1580, 100);
    this->clickScreen(271, 1570, 500);

    // 截图
    cutAnImage("message", "新建-2.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageSearch()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");

    // 搜索输入1
    this->clickScreen(374, 322, 500);
    this->clickScreen(70, 2061, 100);
    this->clickScreen(42, 1580, 100);
    // 截图
    cutAnImage("message", "搜索-1.png", 100);
    // 删除重启
    restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索输入 我
    this->clickScreen(374, 322, 500);
     this->clickScreen(182, 1580, 100);
     this->clickScreen(69, 1410, 500);
    // 截图
    cutAnImage("message", "搜索-2.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageCollection()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // ...
    clickScreen(1012, 147, 500);
    // 我的收藏
    clickScreen(800, 431, 500);
    // 截图
    cutAnImage("message", "我的收藏.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageNotice()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // 通知信息
    clickScreen(370, 458, 500);
    // 搜索 中国联通
    clickScreen(283, 310, 500);

    // 输入中国联通
    clickScreen(220, 1941, 100);
    clickScreen(529, 1761, 100);
    clickScreen(961, 1777, 100);
    clickScreen(493, 1603, 500);
    // 点击
    clickScreen(126, 1420, 500);
    // 选择
    clickScreen(335, 467, 500);
    // 截图
    cutAnImage("message", "联通通知-1.png", 100);
    // 长按
    clickLongTime(518, 1855, 1000);
    // 更多
    clickScreen(854, 1622, 500);
    // 截图
    cutAnImage("message", "联通通知-2.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageRailway()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // 通知信息
    clickScreen(370, 458, 500);
    // 铁路12306
    clickScreen(370, 458, 500);
    // 截图
    cutAnImage("message", "铁路客服-铁路12306‬.png", 100);

    // 长按
    clickLongTime(518, 1689, 1000);
    // 选择文本
    clickScreen(647, 1297, 500);
    // 截图
    cutAnImage("message", "铁路客服-选择文本.png", 100);
    // 返回
    clickScreen(77, 152, 500);
    // 显示原文
    clickScreen(249, 2040, 500);
    // 截图
    cutAnImage("message", "铁路客服-长按显示原文.png", 100);
    // 返回home
    returnHome();
}

void HuaWei9_1_ELE_AL00::messageReports()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(131, 2185, 500);
    // 重启联系人
    restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索输入18500
    this->clickScreen(374, 322, 500);
    this->clickScreen(70, 2061, 100);
    this->clickScreen(42, 1580, 100);
    this->clickScreen(816, 1531, 100);
    this->clickScreen(492, 1570, 100);
    this->clickScreen(1008, 1572, 100);
    this->clickScreen(1008, 1572, 500);
    // 点击短信
    this->clickScreen(482, 425, 500);
    // 长按
    clickLongTime(752, 1369, 1000);
    // 小的更多
    clickScreen(954, 1268, 500);
    // 大的更多
    clickScreen(967, 2153, 500);
    // 查看报告
    clickScreen(771, 1981, 500);
    // 截图
    cutAnImage("message", "查看报告.png", 100);
    // 返回home
    returnHome();
}



void HuaWei9_1_ELE_AL00::totalCutPicture(const QVector<int> &taskLists)
{
    for(int i = 0; i < taskLists.size(); ++i)
    {
        //
        if(this->getPhoneStatues() != devDisConn)
        {
            switch (taskLists[i]) {
               case ContactsList9_1:
                   contactsList();
                   break;
               case ContactsImpExp9_1:
                   contactsImpExp();
                   break;
               case ContactsSetting9_1:
                   contactsSetting();
                   break;
               case ContactsGroup9_1:
                   contactsGroup();
                   break;
               case ContactsLinkedIn9_1:
                   contactsLinkedIn();
                   break;
               case ContactsNew9_1:
                   contactsNew();
                   break;
               // dial -----------------------------------
               case DialDial9_1:
                   dialDial();
                   break;
               case DialMore9_1:
                   dialMore();
                   break;
               case DialDetail9_1:
                   dialDetail();
                   break;
               case DialSave9_1:
                   dialSave();
                   break;
               case DialCollect9_1:
                   dialCollect9_1();
                   break;
               // home ----------------------------------
               case HomeHome9_1:
                   homeHome();
                   break;
               case HomeFolder9_1:
                   homeFolder();
                   break;
               case HomeWallpaper9_1:
                   homeWallpaper9_1();
                   break;
               case HomeList9_1:
                   homeList();
                   break;
               case HomeSetting9_1:
                   homeSetting();
                   break;
               case HomeMenu9_1:
                   homeMenu();
                   break;
               case HomeVolume9_1:
                   homeVolume();
                   break;
               case HomeLock9_1:
                   homeLock();
                   break;
               // message ------------------------------------
               case MessageEmoticon9_1:
                   messageEmoticon9_1();
                   break;
               case MessageList9_1:
                   messageList();
                   break;
               case MessageWebsit9_1:
                   messageWebsit();
                   break;
               case MessageSetting9_1:
                   messageSetting();
                   break;
               case MessageCentre9_1:
                   messageCentre9_1();
                   break;
               case MessagePress9_1:
                   messagePress();
                   break;
               case MessageNew9_1:
                   messageNew();
                   break;
               case MessageSearch9_1:
                   messageSearch();
                   break;
               case MessageCollection9_1:
                   messageCollection();
                   break;
               case MessageNotice9_1:
                   messageNotice();
                   break;
               case MessageRailway9_1:
                   messageRailway();
                   break;
               case MessageReports9_1:
                   messageReports();
                   break;

               default:
                   break;
               }

        }
        else
        {

        }


    }
}
