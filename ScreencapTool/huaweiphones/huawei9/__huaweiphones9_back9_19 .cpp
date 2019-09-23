#include "huaweiphones9.h"
#include "ocrTest.h"
#include <QDebug>
#include <QTextCodec>
#include <QFile>
#include <QDomDocument>

HuaWeiPhones9::HuaWeiPhones9(const PhoneCharacters &phoneCharacters):HuaWeiPhones(phoneCharacters)
{
    init();
    KEYBORDPOS_X = 996;
    KEYBORDPOS_Y = 1439;

    MY_THEME_Y = 705;
    IS_CHECK_KEYBORD;
    SINGAL_KB_SOP_Y;//add
    // 联系人清理
    IS_CLEAN_CALL = false;
    /*<!--联系人：  新建{电话输入 添加群组 添加更多} 群组 设置{设置 关于} 领英！导入导出{从其他设备导入 分享联系人{导入到卡1}}-->*/
    C_NEW_CALL_Y;
    C_NEW_ADDGROUP_Y =1357;
    C_NEW_ADDMORE_Y =1502;
    C_GROUP_Y = 478;
    C_SETTING_Y = 431;
    C_SETTING_ABOUT_Y = 1803;
    C_LINKIN_Y = 862;
    C_IEMP_OTHERS_Y;
    C_IEMP_TOSIM1_Y = 1452;
    /*<!-- dial：设置{更多 通话记录 } !-->*/
    D_SETTING_Y = 879;
    D_SETTING_MORE_Y;// no use
    D_SETTING_MORE_PAGE;//no use
    D_SETTING_RECORD_Y = 684;
    D_SETTING_RECORD_PAGE;

    /*<!-- home：清理 锁屏页面 文件夹添加  !-->*/
    H_CLEAN_PAGE_INDEX = 3;
    H_CLOCK_PAGE_INDEX = 1;
    H_FOLDER_ADD_X = 296;
    H_FOLDER_ADD_Y = 1244;

    /*<!-- message：设置更多{ 高级 短信中心} 长安短信{短信内容 短信上栏小的更多} !-->*/
    M_SETTING_Y = 863;
    M_SETTING_GAOJI_Y = 1292;
    M_SETTING_CENTRE_Y = 1056;
    M_PRESS_MS_Y = 1369;
    M_PRESS_LITTLE_Y = 1268;

    initPosition();
}

Pos HuaWeiPhones9::getTextPozision(const QString &, const QByteArray &text)
{
    QString _tempPath("./temp/temp.png");
    //    _tempPath.append();

    qDebug() << "picPath:" << _tempPath;

    QTextCodec *codec = QTextCodec::codecForLocale();
    codec->setCodecForLocale(QTextCodec::codecForName("UTF-8"));// 编码改变
    //    QString mtext = codec->toUnicode(text.toStdString().c_str());
    char __text[1024] = "";
    strncpy(__text, text.data(), text.size());
    char *_out = "24.9827c9cf9cd3dee2c6a1bea6487b1c0f.2592000.1569481485.282335-16998233";
    GoString token{_out, ptrdiff_t(strlen(_out))};
    GoString _picPath{_tempPath.toStdString().c_str(), ptrdiff_t(_tempPath.size())};
    GoString _text{__text, ptrdiff_t(text.size())};
    // 参数：token, picPath, text
    char *ret = GOcrReadImage(token, _picPath, _text);
    codec->setCodecForLocale(QTextCodec::codecForName("GBK"));// 编码修改回去，不然截图是乱码
    if(ret == NULL)
        return Pos(0, 0);

    qDebug() << "ret:" << ret << "text:" << __text;

    Pos pos(0, 0);
    // 解析
    QString temp(ret);
    if(temp.contains(":")) {
        int i = temp.indexOf(":");
        pos.pos_x = temp.left(i).toInt();
        pos.pos_y = temp.right(temp.size() - i -1).toInt();
    }

    qDebug() << "x:" << pos.pos_x << "y:" << pos.pos_y;

    return pos;
}

void HuaWeiPhones9::init()
{
    adbSystem->setPhoneScreenSize(phoneCharacters.wm_size);
    ScreenSizeT t;
    t.width = 1080;
    t.height = 2244;
    adbSystem->setBaseScreenSize(t);
}


void HuaWeiPhones9::taskIdSwitch(int i)
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

void HuaWeiPhones9::pushThemeToPhone(const QString &themeFile)
{
    // 删除旧的themes
    QString str;
    str.append("rm /sdcard/HuaWei/Themes/*.hwt");

    adbSystem->commondAdbNoResults(str);

    adbSystem->delayMS(100);

    str.clear();
    str.append(QString("push "));
    str.append(themeFile);
    str.append(" /sdcard/HuaWei/Themes/");

    adbSystem->commondAdbNoShell(str);
}

void HuaWeiPhones9::initPicPath()
{
    adbSystem->mkDirInitPicPath();
}

const QString HuaWeiPhones9::getPicturePath()
{
    return adbSystem->getPicPath();
}


void HuaWeiPhones9::themeInstall()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启主题
    adbSystem->restartActvity("com.huawei.android.thememanager/.HwThemeManagerActivity");
    // 我的
    adbSystem->clickScreen(927, 2188, 800);

    // 修改字体
    adbSystem->cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("", "我的字体");
    adbSystem->clickScreen(297, pos.pos_y, 500, NO_CONV_POS);// 有卡
//    adbSystem->clickScreen(297, MY_THEME_Y + 150/*855*/, 500);
    //
    adbSystem->clickScreen(357, 710, 500);

    adbSystem->clickScreen(560, 2175, 800);

    adbSystem->clickScreen(90, 148, 800);

    // 我的主题
    adbSystem->clickScreen(297, pos.pos_y - 150/*705*/, 1000, NO_CONV_POS);
    //
    adbSystem->clickScreen(206, 624, 1000);
    // 279 1990 更新取消
    adbSystem->clickScreen(279, 2102, 500);
    // 应用
    adbSystem->clickScreen(491, 2155, 3000);
    // 279 1990 更新取消
    adbSystem->clickScreen(279, 2102, 500);
    // 不保留 锁屏杂志
    adbSystem->clickScreen(269, 2121, 3000);
    // home
    adbSystem->returnHome();

    if(IS_CLEAN_CALL){
        // 联系人清理 恢复
        // 关闭导航栏
        adbSystem->clickScreen(131, 2185, 500);
        // 重启联系人
        adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
        /*******/
        // 点击电话
        adbSystem->clickScreen(177, 2166, 500);
        // 点击...
        adbSystem->clickScreen(994, 187, 500);
        // 点击批量删除
        adbSystem->clickScreen(835, 572, 500);
        // 全选
        adbSystem->clickScreen(616, 2149, 500);
        // 删除
        adbSystem->clickScreen(440, 2146, 500);
        // 确定
        adbSystem->clickScreen(816, 2098, 500);

        adbSystem->returnHome();
        adbSystem->returnHome();
        // 恢复
        adbSystem->clickScreen(955, 1670, 6000);
        //    adbSystem->restartActvity("com.weining.view.activity/com.weining.backup.ui.activity.HomeActivity");
        adbSystem->clickScreen(910, 1024, 800);
        // 导入
        adbSystem->clickScreen(798, 156, 800);
        //
        adbSystem->clickScreen(478, 582, 800);
        //
        adbSystem->clickScreen(784, 367, 800);
        //
        adbSystem->clickScreen(888, 1330, 800);

        adbSystem->returnHome();
        adbSystem->swipeScreen(500, 2243, 500, 1900, 800);
        adbSystem->clickScreen(777, 2165, 800);
        adbSystem->clickScreen(557, 1986, 800);
    }
}



/********************************************************************/
// 联系人列表
void HuaWeiPhones9::contactsList()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    adbSystem->clickScreen(541, 2176, 500);

    // 截图
    adbSystem->cutAnImage("contacts", "联系人列表-1.png", 100);

    adbSystem->clickScreen(1042, 436, 800);
    // 截图
    adbSystem->cutAnImage("contacts", "联系人列表-2.png", 100);

    // 点击联系人
    adbSystem->clickScreen(541, 2176, 500);
    // 固定联系人
    adbSystem->clickScreen(443, 1966, 500);
    // 点击
    // 截图
    adbSystem->cutAnImage("contacts", "联系人列表-3.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::contactsImpExp()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    adbSystem->clickScreen(541, 2176, 500);

    // 点击...
    adbSystem->clickScreen(1001, 171, 500);
    // 点击设置
    adbSystem->clickScreen(758, C_SETTING_Y/*431*/, 500, NO_CONV_POS);
    // 点击导入导出
    adbSystem->clickScreen(283, 1005, 500);
    // 截图
    adbSystem->cutAnImage("contacts", "导入导出-1.png", 100);
    // 通过蓝牙导入联系人
    adbSystem->clickScreen(301, 448, 500);
    // 截图
    adbSystem->cutAnImage("contacts", "导入导出-2.png", 100);
    // 返回
    adbSystem->clickScreen(78, 154, 500);
    // 点击从卡1导入
    adbSystem->clickScreen(184, C_IEMP_TOSIM1_Y/*1562*/, 500, NO_CONV_POS);
    // 点击全选
//    adbSystem->clickScreen(666, 2148, 500);
    adbSystem->clickScreen(666, 460, 500, NO_CONV_POS);

    adbSystem->clickScreen(666, 653, 500, NO_CONV_POS);

    // 点击导入
//    adbSystem->clickScreen(408, 2148, 500);
    // 截图
    adbSystem->cutAnImage("contacts", "导入导出-3.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::contactsSetting()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    adbSystem->clickScreen(541, 2176, 500);
    // 点击...
    adbSystem->clickScreen(1001, 171, 500, NO_CONV_POS);
    // 点击设置
    adbSystem->clickScreen(758, C_SETTING_Y/*431*/, 500, NO_CONV_POS);
    // 点击关于
    adbSystem->clickScreen(171, C_SETTING_ABOUT_Y/*1803*/, 500, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("contacts", "设置-关于.png", 100);
    // 调出导航栏
    adbSystem->swipeScreen(782, 2217, 782, 1789, 800);
    // 截图
    adbSystem->cutAnImage("contacts", "设置-关于-1.png", 100);
    // 关闭导航栏
    adbSystem->clickScreen(139, 2182, 500);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::contactsGroup()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    adbSystem->clickScreen(541, 2176, 500);
    // 点击群组
    adbSystem->clickScreen(343, C_GROUP_Y/*478*/, 500, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("contacts", "群组-群组.png", 100);
    // 点击新建
    adbSystem->clickScreen(410, 2188, 500);
    // 截图
    adbSystem->cutAnImage("contacts", "群组-新建.png", 100);
    // 输入666
    adbSystem->inputText("666");
    // 截图
    adbSystem->cutAnImage("contacts", "群组-新建-1.png", 100);
    // 返回home
    adbSystem->returnHome();

}

void HuaWeiPhones9::contactsLinkedIn()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    adbSystem->clickScreen(541, 2176, 500);
    // 点击领英
    adbSystem->clickScreen(334, C_LINKIN_Y/*862*/, 500, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("contacts", "领英.png", 100);
    // 返回home
    adbSystem->returnHome();

}

void HuaWeiPhones9::contactsNew()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 点击联系人
    adbSystem->clickScreen(541, 2176, 500);
    // 点击新建
    adbSystem->clickScreen(919, 1963, 500);
    // 截图
    adbSystem->cutAnImage("contacts", "新建-新建联系人.png", 100);

    adbSystem->clickScreen(KEYBORDPOS_X/*996*/, KEYBORDPOS_Y/*1439*/, 500);// 关闭键盘
    // 加入群组
    adbSystem->clickScreen(558, C_NEW_ADDGROUP_Y/*1357*/, 500, NO_CONV_POS);
    //
    adbSystem->cutAnImage("contacts", "新建-新建联系人-加入群组.png", 100);
    // 取消
    adbSystem->clickScreen(113, 151, 500);

    // 添加更多
    adbSystem->clickScreen(217, C_NEW_ADDMORE_Y/*1552*/, 500, NO_CONV_POS);
    // 上滑动
    adbSystem->swipeScreen(716, 1000, 716, 400, 500);
    //    verticalRollToBottom();
    // 日期
    adbSystem->clickScreen(628, 1986, 500);
    // 截图
    adbSystem->cutAnImage("contacts", "新建-新建联系人-添加更多项-日期.png", 100);

    // 返回home
    adbSystem->returnHome();
}

/******************************************************8888888888888888888888888**********/

void HuaWeiPhones9::dialDial()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击电话
    adbSystem->clickScreen(177, 2166, 500);
    // 截图
    adbSystem->cutAnImage("digit","拨号盘-1.png", 100);
    // 关闭键盘
    adbSystem->clickScreen(115, 1960, 500);
    //下滑
    adbSystem->swipeScreen(700, 445, 700, 745, 800);

    // 截图
    adbSystem->cutAnImage("digit","拨号盘-2.png", 100);
    // 上滑动
    adbSystem->swipeScreen(746, 1069, 746, 700, 800);
    // 截图
    adbSystem->cutAnImage("digit","拨号盘-3.png", 100);
    // 打开键盘
    adbSystem->clickScreen(926, 1973, 500);
    // 输入151
    adbSystem->clickScreen(220, 1203, 100);
    adbSystem->clickScreen(526, 1398, 100);
    adbSystem->clickScreen(220, 1203, 500);
    // 截图
    adbSystem->cutAnImage("digit","拨号盘-4.png", 100);
    // 输入1511
    adbSystem->clickScreen(220, 1203, 100);
    adbSystem->clickScreen(526, 1398, 100);
    adbSystem->clickScreen(220, 1203, 100);
    adbSystem->clickScreen(220, 1203, 500);
    // 截图
    adbSystem->cutAnImage("digit","拨号盘-5.png", 100);
    /*******/
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::dialMore()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击电话
    adbSystem->clickScreen(177, 2166, 500);
    // 点击...
    adbSystem->clickScreen(994, 187, 500, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("digit", "更多设置-更多.png", 100);
    // 设置
    adbSystem->clickScreen(764, D_SETTING_Y/*879*/, 500, NO_CONV_POS);
    // 自动通话录音
    adbSystem->clickScreen(244, D_SETTING_RECORD_Y/*684*/, 500, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("digit", "更多设置-通话自动录音.png", 100);

    // 指定号码
    adbSystem->clickScreen(155, 641, 500, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("digit", "更多设置-通话自动录音-1.png", 100);

    /*******/
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::dialDetail()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击电话
    adbSystem->clickScreen(177, 2166, 500);
    // 点击 !
    adbSystem->clickScreen(999, 470, 500);
    //
//    adbSystem->clickScreen(413, 944, 500);
    // 截图
    adbSystem->cutAnImage("digit", "详情-联系人详情.png", 100);

    // 点击 ...
    adbSystem->clickScreen(800, 2155, 500);
    // 点击 标记为
    adbSystem->clickScreen(771, 1845, 500);

    // 截图
    adbSystem->cutAnImage("digit", "详情-联系人详情标记.png", 100);

    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::dialSave()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击电话
    adbSystem->clickScreen(177, 2166, 1000);
    // 长按号码
    adbSystem->clickLongTime(362, 291, 1000, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("digit", "长按保存.png", 100);
    // 保存至已有联系人
    adbSystem->clickScreen(604, 805, 500, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("digit", "长按保存-保存至已有联系人.png", 100);
    /*******/
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::dialCollect9_1()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    /*******/
    // 点击收藏编辑
    adbSystem->clickScreen(900, 2166, 500);
    // 长按
    adbSystem->clickLongTime(555, 600, 1000);
    // 截图
    adbSystem->cutAnImage("digit", "收藏编辑.png", 100);

    /*******/
    // 返回home
    adbSystem->returnHome();
}


/****************************************************************************************************/

void HuaWeiPhones9::homeHome()
{
    // 返回home
    adbSystem->returnHome();
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);

    adbSystem->cutAnImage("home", "桌面-1.png", 100);
    // 左滑
    adbSystem->swipeScreen(239, 1704, 470, 1704, 500);
    // 截屏
    adbSystem->cutAnImage("home","桌面-2.png", 100);
    // 右滑
    adbSystem->swipeScreen(470, 1704, 200, 1704, 500);
    adbSystem->swipeScreen(470, 1704, 200, 1704, 500);

    // 截屏
    adbSystem->cutAnImage("home","桌面-3.png", 100);


    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::homeFolder()
{
    // 返回home
    adbSystem->returnHome();
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 右滑
    adbSystem->swipeScreen(906, 1375, 252, 1375, 500);
    // 文件夹2
    adbSystem->clickScreen(961, 234, 500);
    //截屏
    adbSystem->swipeHalfCutImage(858, 1154, 658, 1154, "home", "文件夹-4.png");
    // 左边滑动
    adbSystem->swipeScreen(858, 1154, 255, 1154, 500);
    // +
    adbSystem->clickScreen(H_FOLDER_ADD_X/*296*/, H_FOLDER_ADD_Y/*1244*/, 500);
    // 截屏
    adbSystem->clickCancelCutImage(298, 2085, 3000, "home", "文件夹添加.png");
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::homeList()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 应用程序
    adbSystem->clickScreen(553, 2083, 500);
    // 截图
    adbSystem->cutAnImage("home","应用列表-1.png", 100);
    // 点击s
    adbSystem->clickScreen(1053, 1620, 1500);
    // 截图
    adbSystem->cutAnImage("home","应用列表-6.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::homeSetting()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 长按
    adbSystem->clickLongTime(974, 1755, 1000);
    // 桌面设置
    adbSystem->clickScreen(913, 1898, 500);
    // 截图
    adbSystem->cutAnImage("home","桌面设置.png", 100);
    // 返回home
    adbSystem->returnHome();
}


void HuaWeiPhones9::homeMenu()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 下拉
    adbSystem->swipeScreen(671, 21, 690, 1628, 500);
    // 展开图标
    adbSystem->swipeScreen(544, 630, 576, 1223, 500);
    // 截图
    adbSystem->cutAnImage("home","桌面下拉.png", 100);
    // 编辑
    adbSystem->clickScreen(814, 187, 500);
    // 截图
    adbSystem->cutAnImage("home","桌面下拉-编辑.png", 100);
    // 返回home
    adbSystem->returnHome();}

void HuaWeiPhones9::homeLock()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 长按
    adbSystem->clickLongTime(974, 1755, 1000);
    // 窗口小工具
    adbSystem->clickScreen(419, 1866, 500);
    // 左边滑动H_CLEAN_PAGE_INDEX次
    for(int i = 0; i < H_CLEAN_PAGE_INDEX; ++i){
        adbSystem->swipeScreen(741, 2083, 300, 2083, 300);
    }

    // 截图
    adbSystem->cutAnImage("home","一键优化.png", 100);
    // 左边滑动H_CLOCK_PAGE_INDEX次
    for(int i = 0; i < H_CLOCK_PAGE_INDEX; ++i){
        adbSystem->swipeScreen(741, 2083, 300, 2083, 300);
    }
    // 截图
    adbSystem->cutAnImage("home","一键锁屏.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::homeVolume()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 按下
    adbSystem->addVolumes();
    // 截图
    adbSystem->cutAnImage("home","音量.png", 100);
    // 返回home
    adbSystem->returnHome();}

void HuaWeiPhones9::homeWallpaper9_1()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 长按
    adbSystem->clickLongTime(974, 1755, 1000);
    // 壁纸
    adbSystem->clickScreen(171, 1925, 1500);
    // 图片
    adbSystem->clickScreen(869, 548, 1000);
    //670 2154
    adbSystem->clickScreen(670, 2154, 500);
    // 截图
    adbSystem->cutAnImage("home","桌面壁纸.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageEmoticon9_1()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索输入18500
    this->adbSystem->clickScreen(374, 322, 800);
    adbSystem->inputText("18500");

    // 点击短信
    this->adbSystem->clickScreen(482, 425, 500);
    // 点击表情
    this->adbSystem->clickScreen(867, 2171, 500);
    // 点击三角形
    this->adbSystem->clickScreen(859, 2198, 500);
    // 截图
    adbSystem->cutAnImage("message", "表情符号-0.png", 100);
    // 点击表情
    adbSystem->clickScreen(241, 2195, 500);
    // 截图
    adbSystem->cutAnImage("message", "表情符号-1.png", 100);
    // 返回home
    adbSystem->returnHome();

}

void HuaWeiPhones9::messageCentre9_1()
{ // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 点击...
    this->adbSystem->clickScreen(1018, 155, 500);
    // 点击设置
    adbSystem->clickScreen(744, M_SETTING_Y/*863*/, 500, NO_CONV_POS);
    // 高级
    adbSystem->clickScreen(306, M_SETTING_GAOJI_Y/*1292*/, 500, NO_CONV_POS);
    // 卡2 短信中心
    adbSystem->clickScreen(303, M_SETTING_CENTRE_Y/*1056*/, 500, NO_CONV_POS);
    // 截图
    adbSystem->cutAnImage("message", "短信中心.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageList()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    /*******/
    // 截图1
    adbSystem->cutAnImage("message", "短信列表-1.png", 100);
    // 截图2
    adbSystem->swipeScreen(660, 1350, 660, 900, 500);
    adbSystem->cutAnImage("message", "短信列表-2.png", 100);
    // 长按短信
    adbSystem->clickLongTime(701, 871, 1000);
    // 截图
    adbSystem->cutAnImage("message", "短信列表-3.png", 100);
    /*******/
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageWebsit()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索输入18630
    this->adbSystem->clickScreen(374, 322, 800);
    adbSystem->inputText("15122139813");

    // 点击短信
    this->adbSystem->clickScreen(482, 425,500);
    // 截图
    adbSystem->cutAnImage("message", "恶意网址.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageSetting()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 点击...
    this->adbSystem->clickScreen(1018, 155, 500);
    // 截图
    adbSystem->cutAnImage("message", "设置-更多.png", 100);
    // 点击拦截骚扰
    this->adbSystem->clickScreen(779, 583, 500);
    // 点击 拦截规则
    adbSystem->clickScreen(799, 2163, 800);
    // 截图
    adbSystem->cutAnImage("message", "设置-设置.png", 100);
    // 返回home
    adbSystem->returnHome();

}

void HuaWeiPhones9::messagePress()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    // 搜索输入18500
    this->adbSystem->clickScreen(374, 322, 700);
    adbSystem->inputText("18500");

    // 点击短信
    this->adbSystem->clickScreen(482, 425, 500);
    // 长按
    adbSystem->clickLongTime(752, M_PRESS_MS_Y/*1369*/, 1000);
    // 截图
    adbSystem->cutAnImage("message", "长按短信-1.png", 100);
    // 小的更多
    adbSystem->clickScreen(954, M_PRESS_LITTLE_Y/*1268*/, 500);
    // 截图
    adbSystem->cutAnImage("message", "长按短信-2.png", 100);
    // 大的更多
    adbSystem->clickScreen(967, 2153, 500);
    // 截图
    adbSystem->cutAnImage("message", "长按短信-3.png", 100);
    // 查看详情
    adbSystem->clickScreen(800, 1829, 500);
    // 截图
    adbSystem->cutAnImage("message", "长按短信-4.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageNew()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // +
    adbSystem->clickScreen(948, 2131, 500);

    // 输入123
    adbSystem->clickScreen(241, 308, 600);
    adbSystem->inputText("123");

    // 截图
    adbSystem->cutAnImage("message", "新建-1.png", 100);
    //    adbSystem->inputText("22139813");

    // 点击短信
//    this->adbSystem->clickScreen(482, 425, 500);
    // 搜索
//    this->adbSystem->clickLongTime(874, 322, 1000);
    // 换行
    adbSystem->clickScreen(966, 2101, 500);
    // 截图
    adbSystem->cutAnImage("message", "新建-2.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageSearch()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    // 搜索输入1
    this->adbSystem->clickScreen(374, 322, 500);
    adbSystem->inputText("1");

    // 截图
    adbSystem->cutAnImage("message", "搜索-1.png", 100);
    adbSystem->delTexts(2);

    adbSystem->inputText("w");

    // 截图
    adbSystem->cutAnImage("message", "搜索-2.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageCollection()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // ...
    adbSystem->clickScreen(1012, 147, 500);
    // 我的收藏
    adbSystem->clickScreen(800, 431, 500);
    // 截图
    adbSystem->cutAnImage("message", "我的收藏.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageNotice()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 通知信息
    adbSystem->clickScreen(370, 458, 500);
    // 搜索 中国联通
    adbSystem->clickScreen(283, 310, 500);

    // 输入10010
    adbSystem->inputText("10010");

    // 选择
    adbSystem->clickScreen(335, 467, 500);
    // 截图
    adbSystem->cutAnImage("message", "联通通知-1.png", 100);
    // 长按
//    adbSystem->clickLongTime(518, 1855, 1000);
    // 更多
//    adbSystem->clickScreen(854, 1622, 500);

    adbSystem->clickScreen(903, 2174, 500);
    // 截图
    adbSystem->cutAnImage("message", "联通通知-2.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageRailway()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 通知信息
    adbSystem->clickScreen(370, 458, 500);
    //  搜索
    adbSystem->clickScreen(283, 310, 500);

    // 12306
    adbSystem->inputText("12306");
    // 选择
    adbSystem->clickScreen(335, 467, 500);
    // 截图
    adbSystem->cutAnImage("message", "铁路客服-铁路12306.png", 100);

    // 长按
    adbSystem->clickLongTime(518, 1689, 1000);
    // 选择文本
    adbSystem->clickScreen(647, 1297, 500);
    // 截图
    adbSystem->cutAnImage("message", "铁路客服-选择文本.png", 100);
    // 返回
    adbSystem->clickScreen(77, 152, 500);
    // 显示原文
    adbSystem->clickScreen(249, 2040, 500);
    // 截图
    adbSystem->cutAnImage("message", "铁路客服-长按显示原文.png", 100);
    // 返回home
    adbSystem->returnHome();
}

void HuaWeiPhones9::messageReports()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(131, 2185, 500);
    // 重启联系人
    adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索输入18500
    this->adbSystem->clickScreen(374, 322, 500);
    adbSystem->inputText("1850036");

    // 点击短信
    this->adbSystem->clickScreen(482, 425, 500);
    // 长按
    adbSystem->clickLongTime(752, M_PRESS_MS_Y/*1369*/, 1000);
    // 小的更多
    adbSystem->clickScreen(954, M_PRESS_LITTLE_Y/*1268*/, 500);
    // 大的更多
    adbSystem->clickScreen(967, 2153, 500);
    // 查看报告
    adbSystem->clickScreen(771, 1981, 500);
    // 截图
    adbSystem->cutAnImage("message", "查看报告.png", 100);
    // 返回home
    adbSystem->returnHome();
}



void HuaWeiPhones9::initPosition()
{
    QFile file("./plugins/xml/position.xml");
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << "huawei9.xml is not exit";
        return;
    }

    //
    QDomDocument doc;
    if(!doc.setContent(&file)){
        qCritical() << "doc set file failed..";
        file.close();
        return;
    }

    file.close();
    // 根节点
    QDomElement root = doc.documentElement();
    qDebug() << "root:" << root.nodeName();
    QDomNode node = root.firstChild();// 获取第一个子节点
    while(!node.isNull()){
        if(node.isElement()){// 找到节点
            QDomElement n = node.toElement();
            qDebug() << n.nodeName() << n.attribute("id");// << de.attribute("time");// 获取标签属性 名称

            if(n.attribute("id") == phoneCharacters.phoneSerial){
                QDomNodeList list = n.childNodes();
                for(int i = 0; i < list.size(); ++i){
                    QDomNode de = list.at(i);

                    if(de.nodeName() == "key_board_x"){
                        KEYBORDPOS_X = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "key_board_y"){
                        KEYBORDPOS_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "my_theme_y"){
                        MY_THEME_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "is_ckeck_keyboard"){
                        IS_CHECK_KEYBORD = (de.toElement().text().toInt() == 0);
                    }
                    if(de.nodeName() == "singal_kb_sop_y"){
                        SINGAL_KB_SOP_Y = (de.toElement().text().toInt() == 0);
                    }
                    if(de.nodeName() == "is_clean_call"){
                        IS_CLEAN_CALL = (de.toElement().text().toInt() == 0);
                    }

                    if(de.nodeName() == "c_new_call_y"){
                        C_NEW_CALL_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "c_new_addG_y"){
                        C_NEW_ADDGROUP_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "c_new_addM_y"){
                        C_NEW_ADDMORE_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "c_group_y"){
                        C_GROUP_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "c_set_y"){
                        C_SETTING_Y = de.toElement().text().toInt();
                    }

                    if(de.nodeName() == "c_set_about_y"){
                        C_SETTING_ABOUT_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "c_linkin_y"){
                        C_LINKIN_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "c_IEmp_others_y"){
                        C_IEMP_OTHERS_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "c_IEmp_toSIM1_y"){
                        C_IEMP_TOSIM1_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "d_set_y"){
                        D_SETTING_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "d_set_more_y"){
                        if(de.toElement().attribute("page") == "1")
                            D_SETTING_MORE_PAGE = '1';
                        else
                            D_SETTING_MORE_PAGE = '2';
                        D_SETTING_MORE_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "d_set_record_y"){
                        if(de.toElement().attribute("page") == "1")
                            D_SETTING_RECORD_PAGE = '1';
                        else
                            D_SETTING_RECORD_PAGE = '2';
                        D_SETTING_RECORD_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "h_clean_page_index"){
                        H_CLEAN_PAGE_INDEX = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "h_lock_page_index"){
                        H_CLOCK_PAGE_INDEX = de.toElement().text().toInt();
                    }

                    if(de.nodeName() == "h_folder_add_x"){
                        H_FOLDER_ADD_X = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "h_folder_add_y"){
                        H_FOLDER_ADD_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_set_y"){
                        M_SETTING_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_set_gaoji_y"){
                        M_SETTING_GAOJI_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_set_centre_y"){
                        M_SETTING_CENTRE_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_press_ms_y"){
                        M_PRESS_MS_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_press_little_y"){
                        M_PRESS_LITTLE_Y = de.toElement().text().toInt();
                    }

                }
            }
        }
        node = node.nextSibling();//与nextSiblingElement差不多
    }

    test();
}

void HuaWeiPhones9::test()
{
    qDebug() << "KEYBORDPOS_X:"<< KEYBORDPOS_X;
    qDebug() << "KEYBORDPOS_Y:" << KEYBORDPOS_Y;
    qDebug() << "MY_THEME_Y:" << MY_THEME_Y;
    qDebug() << "IS_CHECK_KEYBORD"<< IS_CHECK_KEYBORD;
    qDebug() << "SINGAL_KB_SOP_Y:" << SINGAL_KB_SOP_Y;
    qDebug() << "IS_CLEAN_CALL:" << IS_CLEAN_CALL;

    qDebug() << "C_NEW_CALL_Y:" << C_NEW_CALL_Y;
    qDebug() << "C_NEW_ADDGROUP_Y:" << C_NEW_ADDGROUP_Y;
    qDebug() << "C_NEW_ADDMORE_Y:" << C_NEW_ADDMORE_Y;
    qDebug() << "C_GROUP_Y:" << C_GROUP_Y;
    qDebug() << "C_SETTING_Y:" << C_SETTING_Y;
    qDebug() << "C_SETTING_ABOUT_Y:" << C_SETTING_ABOUT_Y;
    qDebug() << "C_LINKIN_Y:" << C_LINKIN_Y;
    qDebug() << "C_IEMP_OTHERS_Y:" << C_IEMP_OTHERS_Y;
    qDebug() << "C_IEMP_TOSIM1_Y:" << C_IEMP_TOSIM1_Y;
    qDebug() << "D_SETTING_Y:" << D_SETTING_Y;
    qDebug() << "D_SETTING_MORE_PAGE:" << D_SETTING_MORE_PAGE;
    qDebug() << "D_SETTING_MORE_Y:" << D_SETTING_MORE_Y;
    qDebug() << "D_SETTING_RECORD_PAGE:" << D_SETTING_RECORD_PAGE;
    qDebug() << "D_SETTING_RECORD_Y:" << D_SETTING_RECORD_Y;
    qDebug() << "H_CLEAN_PAGE_INDEX:" << H_CLEAN_PAGE_INDEX;
    qDebug() << "H_CLOCK_PAGE_INDEX:" << H_CLOCK_PAGE_INDEX;
    qDebug() << "H_FOLDER_ADD_X:" << H_FOLDER_ADD_X;
    qDebug() << "H_FOLDER_ADD_Y:" << H_FOLDER_ADD_Y;
    qDebug() << "M_SETTING_Y:" << M_SETTING_Y;
    qDebug() << "M_SETTING_GAOJI_Y:" << M_SETTING_GAOJI_Y;
    qDebug() << "M_SETTING_CENTRE_Y:" << M_SETTING_CENTRE_Y;
    qDebug() << "M_PRESS_MS_Y:" << M_PRESS_MS_Y;
    qDebug() << "M_PRESS_LITTLE_Y:" << M_PRESS_LITTLE_Y;
}

