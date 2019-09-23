#include "huaweiphones8.h"
#include <QTextCodec>
#include "ocrTest.h"
#include <QDebug>
#include "imagecompare.h"
#include <QDomDocument>
#include <QFile>
#include <QDomNode>


HuaWeiPhones8::HuaWeiPhones8(const PhoneCharacters &phoneCharacters):HuaWeiPhones(phoneCharacters)
{
    init();

    KEYBORDPOS_X;
    KEYBORDPOS_Y = 1385; //no use

    IS_CHECK_KEYBORD = true;
    SINGAL_KB_SOP_Y = 617;//add
    /*<!--联系人：  新建{电话输入 添加群组 添加更多} 群组 设置关于 领英！导入导出{从其他设备导入 分享联系人{导入到卡1}}-->*/
    C_NEW_CALL_Y = 645;
    C_NEW_ADDGROUP_Y = 1145;
    C_NEW_ADDMORE_Y = 1336;
    C_GROUP_Y = 532;
    C_SETTING_ABOUT_Y = 1347;
    C_LINKIN_Y = 835;
    C_IEMP_OTHERS_Y = 676;
    C_IEMP_TOSIM1_Y = 931;
    /*<!-- dial：设置{更多 通话记录 来电拒绝[页码]} !-->*/
    D_SETTING_MORE_Y;// no use
    D_SETTING_MORE_PAGE;//no use
    D_SETTING_RECORD_Y = 683;
    D_SETTING_RECORD_PAGE = '1';
    D_SETTING_REJECT_Y = 1677;
    D_SETTING_REJECT_PAGE = '2';

    H_FOLDER_ADD_X = 804;
    H_FOLDER_ADD_Y = 1023;
    H_SETTING_SEARCH_Y = 1094;//change

    M_SETTING_SERVICES_Y = 282;
    M_SETTING_GAOJI_Y = 1244;
    M_SETTING_OFTEN_Y = 301;
    M_SETTING_MARK_Y = 449;
    M_SETTING_CENTRE_Y = 150;
    M_PRESS_LITTLE_Y = 1220;
    ocrToken = "24.9827c9cf9cd3dee2c6a1bea6487b1c0f.2592000.1569481485.282335-16998233";
    // xml
    initPosition();

}



Pos HuaWeiPhones8::getTextPozision(const QString &, const QByteArray &text)
{
    QString _tempPath("./temp/temp.png");
    //    _tempPath.append();

    qDebug() << "picPath:" << _tempPath;

    QTextCodec *codec = QTextCodec::codecForLocale();
    codec->setCodecForLocale(QTextCodec::codecForName("UTF-8"));// 编码改变
    //    QString mtext = codec->toUnicode(text.toStdString().c_str());
    char __text[1024] = "";
    strncpy(__text, text.data(), text.size());
    char _out[264] = "";
    strcpy(_out, ocrToken.toStdString().c_str());
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

void HuaWeiPhones8::taskIdSwitch(int i)
{
    switch (i) {
    case ContactsList:
        contactsList();
        break;
    case ContactsImpExp:
        contactsImpExp();
        break;
    case ContactsSetting:
        contactsSetting();
        break;
    case ContactsGroup:
        contactsGroup();
        break;
    case ContactsLinkedIn:
        contactsLinkedIn();
        break;
    case ContactsNew:
        contactsNew();
        break;
    case DialDial:
        dialDial();
        break;
    case DialKeybord:
        dialKeybord();
        break;
    case DialMore:
        dialMore();
        break;
    case DialDetail:
        dialDetail();
        break;
    case DialMark:
        dialMark();
        break;
    case DialSave:
        dialSave();
        break;
    case HomeHome:
        homeHome();
        break;
    case HomeFolder:
        homeFolder();
        break;
    case HomeNetwork:
        homeNetwork();
        break;
    case HomeList:
        homeList();
        break;
    case HomeSetting:
        homeSetting();
        break;
    case HomeMenu:
        homeMenu();
        break;
    case HomeLock:
        homeLock();
        break;
    case HomePower:
        homePower();
        break;
    case HomeSimpleMode:
        homeSimpleMode();
        break;
    case HomeVolume:
        homeVolume();
        break;
    case MessageList:
        messageList();
        break;
    case MessageNavbar:
        messageNavbar();
        break;
    case MessageSend:
        messageSend();
        break;
    case MessageWebsit:
        messageWebsit();
        break;
    case MessageSetting:
        messageSetting();
        break;
    case MessagePress:
        messagePress();
        break;
    case MessageNew:
        messageNew();
        break;
    case MessageSearch:
        messageSearch();
        break;
    case MessageCollection:
        messageCollection();
        break;
    case MessageNotice:
        messageNotice();
        break;
    case MessageRailway:
        messageRailway();
        break;
    case MessageReports:
        messageReports();
        break;
    default:
        break;
    }
}





void HuaWeiPhones8::initPicPath()
{
    adbSystem->mkDirInitPicPath();
}

const QString HuaWeiPhones8::getPicturePath()
{
    return adbSystem->getPicPath();
}

// 单手键盘关闭检查
void HuaWeiPhones8::recoverEnv()
{
    adbSystem->returnHome();

    // 右滑屏幕
    adbSystem->swipeScreen(938, 1098, 214, 1039, 500);
    // 设置
    adbSystem->clickScreen(555, 218, 500);

    adbSystem->swipeScreen(818, 2033, 818, 1300, 700);
    // 系统
    adbSystem->clickScreen(358, 1702, 500);
    // 单手操作
    adbSystem->clickScreen(555, 617, 500);
    // 单手键盘
    adbSystem->clickScreen(555, 429, 500);

    // 截图
    adbSystem->cutAnImage("..", "temp.png", 100);

    bool ret = keyBoardIsDown("temp.png");
    // 关闭单手键盘
    if(ret != true) {
        adbSystem->clickScreen(943, 1429, 500);
    }
}


bool HuaWeiPhones8::keyBoardIsDown(const QString &img)
{
    QString basePath(getPicturePath());
    QString tempPath(getPicturePath());
    basePath.append("../../baseimg/keyboard.png");
    tempPath.append("../");
    tempPath.append(img);

    int ret = -1;
    ImageCompare compare;
    ret = compare.compareImageResults(basePath, tempPath, 880, 1398, 150, 64);

    qDebug() << "ret object :" <<ret;

    if(ret == 1) {
        return false;
    } else {
        return true;
    }
}


void HuaWeiPhones8::themeInstall()
{
    // 返回home
    adbSystem->returnHome();
    // 关闭导航栏
    adbSystem->clickScreen(76, 2105, 500);
    // 重启主题
    adbSystem->restartActvity("com.huawei.android.thememanager/.HwThemeManagerActivity");
    adbSystem->delayMS(1000);
    // 我的
    adbSystem->clickScreen(977, 2090, 1000, SCALING_POS);
    //    // 上滑动
    //    adbSystem->swipeScreen(838, 1933, 838, 500, 1000);
    // 字体恢复
    adbSystem->cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("", "我的字体");
    adbSystem->clickScreen(pos.pos_x, pos.pos_y, 500, NO_CONV_POS);// 有卡
//    adbSystem->clickScreen(295, 856, 500, NO_CONV_POS);

    adbSystem->clickScreen(344, 725, 500, NO_CONV_POS);

    adbSystem->clickScreen(551, 2076, 1000, SCALING_POS);

    //returnBack(1000);
    adbSystem->clickScreen(76, 120, 1000, NO_CONV_POS);// 返回

    //  // 我的主题
    // 我的
    adbSystem->clickScreen(977, 2090, 1000, SCALING_POS);
    adbSystem->clickScreen(228, pos.pos_y - 150, 1000, NO_CONV_POS);
    // 选中主题
    adbSystem->clickScreen(226, 660, 1000, NO_CONV_POS);
    // 应用
    adbSystem->clickScreen(555, 2078, 1000,SCALING_POS);

    // 不保留 锁屏杂志
    adbSystem->clickScreen(780, 2021, 2000,SCALING_POS);
    // home
    adbSystem->returnHome();

    // 关闭
    if(IS_CHECK_KEYBORD)
        recoverEnv();
}


void HuaWeiPhones8::pushThemeToPhone(const QString &themeFile)
{
    // 删除旧的themes
    QString str;
    str.append("rm /sdcard/HuaWei/Themes/*.hwt");

    //adbProcess.execAdbCommod(str);
    adbSystem->commondAdbNoResults(str);

    adbSystem->delayMS(100);

    str.clear();
    str.append(QString("push "));
    str.append(themeFile);
    str.append(" /sdcard/HuaWei/Themes/");

    adbSystem->commondAdbNoShell(str);
}


//**********************************************
// contacts
void HuaWeiPhones8::contactsList()
{
    adbSystem->returnHome();
    adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");

    // 联系人点击
    adbSystem->clickScreen(541, 142, 500, NO_CONV_POS);
    adbSystem->cutAnImage("contacts", "联系人列表-1.png", 100);
    // 滑动 err

    adbSystem->swipeScreen(598, 1648, 598, 1000, 500);
    //adbSystem->clickScreen(598, 1648, 500);
    adbSystem->cutAnImage("contacts", "联系人列表-4.png", 100);

    adbSystem->returnHome();
}



void HuaWeiPhones8::contactsImpExp()
{
    adbSystem->returnHome();
    adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
    adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
    adbSystem->clickScreen(511, 146, 500);
    // 更多
   adbSystem->clickScreen(783, 2063, 500);
    // 导入导出
   adbSystem->clickScreen(875, 1758, 500);
   adbSystem->cutAnImage("contacts", "导入导出-导入导出.png", 100);
    // 从其他设备导入
   adbSystem->clickScreen(865, C_IEMP_OTHERS_Y/*676*/, 500);// 有卡
   adbSystem->cutAnImage("contacts", "导入导出-从其他设备导入.png", 100);
    // 下一步
   adbSystem->clickScreen(859, 2041, 500);
   adbSystem->cutAnImage("contacts", "导入导出-从其他设备导入-1.png", 100);
    // 返回
   adbSystem->clickScreen(92, 140, 500);
    // 分享联系人
   adbSystem->clickScreen(820, C_IEMP_TOSIM1_Y/*931*/, 500);// 卡1
    // 选择1个
   adbSystem->clickScreen(974, 531, 500);
   adbSystem->cutAnImage("contacts", "导入导出-导出到卡1-1.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::contactsSetting()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
   adbSystem->clickScreen(529, 133, 500);
    // 更多
   adbSystem->clickScreen(799, 2075, 500);
    // 设置
   adbSystem->clickScreen(915, 1937, 500);
   adbSystem->cutAnImage("contacts", "设置-设置.png", 100);
    // 关于
   adbSystem->clickScreen(811, C_SETTING_ABOUT_Y/*1347*/, 500);
   adbSystem->cutAnImage("contacts", "设置-关于.png", 100);
    // 滑动屏幕
   adbSystem->swipeScreen(796, 2155, 796, 1500, 800);
   adbSystem->cutAnImage("contacts", "设置-关于-1.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::contactsGroup()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
   adbSystem->clickScreen(560, 138, 500);
    // 群组
   adbSystem->clickScreen(747, C_GROUP_Y/*532*/, 500);
    // 新建
   adbSystem->clickScreen(431, 2080, 500);
    adbSystem->clickCancelCutImage(328, 1163, 2000, "contacts", "群组-新建.png");
    //cutAnImage("contacts", "群组-新建.png", 100);
   adbSystem->clickScreen(431, 2080, 500);
    //
   adbSystem->inputText("666");

   adbSystem->cutAnImage("contacts", "群组-新建-1.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::contactsLinkedIn()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
   adbSystem->clickScreen(539, 167, 500);
    // 我
   adbSystem->clickScreen(616, C_LINKIN_Y/*835*/, 500);
   adbSystem->cutAnImage("contacts", "领英.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::contactsNew()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
   adbSystem->clickScreen(538, 147, 500);
    // +
   adbSystem->clickScreen(311, 2041, 500);
   adbSystem->cutAnImage("contacts", "新建-新建联系人.png", 100);
    // 头像
   adbSystem->clickScreen(122, 439, 500);
   adbSystem->cutAnImage("contacts", "新建-编辑头像.png", 100);
    // 空白点击
   adbSystem->clickScreen(846, 1567, 500);
    // 电话号码点击
   adbSystem->clickScreen(699, C_NEW_CALL_Y/*653*/, 500);
    // 666
   adbSystem->inputText("666");
   adbSystem->cutAnImage("contacts", "新建-电话号码.png", 100);
    // 清除输入
   adbSystem->clickScreen(1006, C_NEW_CALL_Y/*641*/, 500);
    // 手机
   adbSystem->clickScreen(442, C_NEW_CALL_Y/*642*/, 500);
   adbSystem->cutAnImage("contacts", "新建-手机.png", 100);
    // 空白点击
   adbSystem->clickScreen(846, 1567, 500);
    // 加入群组
   adbSystem->clickScreen(522, C_NEW_ADDGROUP_Y/*1145*/, 500);
   adbSystem->cutAnImage("contacts", "新建-新建联系人-加入群组.png", 100);
    // 取消
   adbSystem->clickScreen(73, 174, 500);
    // 添加其他项
   adbSystem->clickScreen(557, C_NEW_ADDMORE_Y/*1256*/, 500);
    // 生日
   adbSystem->clickScreen(458, 1469, 500);
    // 截取
   adbSystem->cutAnImage("contacts", "新建-新建联系人-添加更多项-日期.png", 100);

   adbSystem->returnHome();
}


//**********************************************
// digit

void HuaWeiPhones8::dialDial()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");

    // 拨号
   adbSystem->clickScreen(175, 127, 500);
    adbSystem->delayMS(500);
   adbSystem->cutAnImage("digit", "拨号盘-1.png", 100);
    // 151
   adbSystem->clickScreen(252, 1278, 100);
   adbSystem->clickScreen(551, 1487, 100);
   adbSystem->clickScreen(232, 1279, 500);
   adbSystem->cutAnImage("digit", "拨号盘-2.png", 100);
    // 1511
   adbSystem->clickScreen(225, 1256, 100);
   adbSystem->clickScreen(567, 1464, 100);
   adbSystem->clickScreen(241, 1279, 100);
   adbSystem->clickScreen(240, 1263, 500);
   adbSystem->cutAnImage("digit", "拨号盘-6.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::dialMore()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 拨号
   adbSystem->clickScreen(183, 134, 500);
    // ...
   adbSystem->clickScreen(887, 2044, 500);
    // 设置
   adbSystem->clickScreen(893, 1834, 800);
    // 下滑
    adbSystem->verticalRollToTop();
   adbSystem->cutAnImage("digit", "更多设置-设置.png", 100);
    if(D_SETTING_REJECT_PAGE == '1'){
        // 来电拒接短信
       adbSystem->clickScreen(701, D_SETTING_REJECT_Y/*1677*/, 500);
       adbSystem->cutAnImage("digit", "更多设置-来电拒接短信.png", 100);
        // 返回
       adbSystem->clickScreen(116, 141, 500);
    }
    if(D_SETTING_RECORD_PAGE == '1'){
        // 通话自动录音
       adbSystem->clickScreen(788, D_SETTING_RECORD_Y/*683*/, 500);
       adbSystem->cutAnImage("digit", "更多设置-通话自动录音.png", 100);
        // 指定号码
       adbSystem->clickScreen(732, 649, 500);
       adbSystem->cutAnImage("digit", "更多设置-通话自动录音-1.png", 100);
        // 返回
       adbSystem->clickScreen(116, 141, 500);

       adbSystem->clickScreen(116, 141, 500);

    }

    // 滑动到底部
   adbSystem->verticalRollToBottom();
//   adbSystem->swipeScreen(638, 2002, 638, 500, 800);
   adbSystem->cutAnImage("digit", "更多设置-设置-1.png", 100);

    if(D_SETTING_RECORD_PAGE == '2'){
        // 通话自动录音
       adbSystem->clickScreen(788, D_SETTING_RECORD_Y, 500);
       adbSystem->cutAnImage("digit", "更多设置-通话自动录音.png", 100);
        // 指定号码
       adbSystem->clickScreen(732, 649, 500);
       adbSystem->cutAnImage("digit", "更多设置-通话自动录音-1.png", 100);
        // 返回
       adbSystem->clickScreen(116, 141, 500);
       adbSystem->clickScreen(116, 141, 500);

    }

    if(D_SETTING_REJECT_PAGE == '2'){
        // 来电拒接短信
       adbSystem->clickScreen(701, D_SETTING_REJECT_Y, 500);
       adbSystem->cutAnImage("digit", "更多设置-来电拒接短信.png", 100);
    }

   adbSystem->returnHome();
}
void HuaWeiPhones8::dialDetail()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 拨号
   adbSystem->clickScreen(181, 157, 500);
    // 收起键盘
   adbSystem->clickScreen(242, 2043, 500);
   adbSystem->cutAnImage("digit", "详情-收起拨号盘.png", 100);
    // i
   adbSystem->clickScreen(1018, 399, 500);
   adbSystem->cutAnImage("digit", "详情-联系人详情-1.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::dialSave()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");

    // 拨号
   adbSystem->clickScreen(183, 176, 1500);
    // 长按第一个号码
   adbSystem->clickLongTime(292, 423, 1000);
   adbSystem->cutAnImage("digit", "长按保存.png", 100);
    // 保存至已有联系人
   adbSystem->clickScreen(536, 970, 500);
   adbSystem->cutAnImage("digit", "长按保存-保存至已有联系人.png", 100);

   adbSystem->returnHome();
}

void HuaWeiPhones8::dialKeybord()
{
   adbSystem->returnHome();
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);

    // 首先从系统设置打开单手键盘
    // 右滑屏幕
   adbSystem->swipeScreen(938, 1098, 214, 1039, 500);
    // 设置
   adbSystem->clickScreen(555, 218, 500);

//   adbSystem->verticalRollToBottom();
   adbSystem->swipeScreen(818, 2033, 818, 1300, 700);
    // 系统
   adbSystem->clickScreen(358, 1702, 500);
    // 单手操作
   adbSystem->clickScreen(555, SINGAL_KB_SOP_Y/*617*/, 500);
    // 单手键盘
   adbSystem->clickScreen(555, 429, 500);
    // 开启
   adbSystem->clickScreen(943, 1429, 500);

    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 拨号
   adbSystem->clickScreen(183, 176, 500);

    // 键盘左上角
   adbSystem->clickScreen(39, 1301, 500);
    // 删除
   adbSystem->clickScreen(684, 2044, 500);
    // 拨号
   adbSystem->clickScreen(183, 176, 500);
   adbSystem->cutAnImage("digit", "单手键盘-1.png", 100);
    // 按住并截图
     // 键盘切到右边
   adbSystem->clickScreen(939, 1664, 500);
   adbSystem->clickScreen(941, 1667, 500);
   adbSystem->cutAnImage("digit", "单手键盘-2.png", 100);

   adbSystem->clickScreen(989, 2044, 500);
   adbSystem->cutAnImage("digit", "单手键盘-3.png", 100);

   adbSystem->returnHome();
   adbSystem->returnHome();
    // 右滑屏幕
   adbSystem->swipeScreen(938, 1098, 214, 1039, 500);
    // 设置
   adbSystem->clickScreen(555, 218, 500);
    //delayMS(500);

   adbSystem->swipeScreen(818, 2033, 818, 1300, 700);
    // 系统
   adbSystem->clickScreen(358, 1702, 500);
    // 单手操作
   adbSystem->clickScreen(555, SINGAL_KB_SOP_Y/*617*/, 500);
    // 单手键盘
   adbSystem->clickScreen(555, 429, 500);
    // 关闭
   adbSystem->clickScreen(943, 1429, 500);

   adbSystem->returnHome();

}

void HuaWeiPhones8::dialMark()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 拨号
   adbSystem->clickScreen(183, 176, 1000);
//    delayMS(500);
    // 长按第一个号码
   adbSystem->clickLongTime(308, 456, 1000);
    // 标记为
   adbSystem->clickScreen(457, 694, 500);
   adbSystem->cutAnImage("digit", "标记-标记为.png", 100);

   adbSystem->returnHome();
}

/*******************************************************/
//home

void HuaWeiPhones8::homeHome()
{
   adbSystem->returnHome();
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);

   adbSystem->cutAnImage("home", "桌面-1.png", 100);
    // 左滑屏幕
   adbSystem->swipeScreen(239, 986, 829, 960, 100);
   adbSystem->cutAnImage("home", "桌面-2.png", 100);
   adbSystem->returnHome();
    // 右滑屏幕
   adbSystem->swipeScreen(839, 986, 329, 960, 10);
   adbSystem->cutAnImage("home", "桌面-3.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::homeFolder()
{
   adbSystem->returnHome();
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);

    // 左滑屏幕
   adbSystem->swipeScreen(931, 1029, 309, 1055, 800);
    // 文件夹
   adbSystem->clickScreen(973, 205, 500);
    //cutAnImage("home", "文件夹-4.png", 100);
    //左滑屏幕
    //swipeScreen(849, 1183, 214, 1179, 800);
    adbSystem->swipeHalfCutImage(849, 1183, 555, 1179, "home", "文件夹-4.png");

   adbSystem->swipeScreen(849, 1183, 214, 1179, 500);
   adbSystem->swipeScreen(849, 1183, 214, 1179, 500);
    // +
   adbSystem->clickScreen(H_FOLDER_ADD_X/*804*/, H_FOLDER_ADD_Y/*1023*/, 500);

    adbSystem->clickCancelCutImage(305, 2028, 2000, "home", "文件夹添加.png");

   adbSystem->returnHome();
}
void HuaWeiPhones8::homeList()
{
   adbSystem->returnHome();
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);

    // 应用
   adbSystem->clickScreen(543, 2010, 500);
   adbSystem->cutAnImage("home", "应用列表-2.png", 100);
    // J
   adbSystem->clickScreen(1040, 1032, 500);
   adbSystem->cutAnImage("home", "应用列表-3.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::homeSetting(){
   adbSystem->returnHome();
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);

    //设置.json begin:
    // 长按
   adbSystem->clickLongTime(989, 1699, 1000);
    // 设置
   adbSystem->clickScreen(915, 1815, 500);
   adbSystem->cutAnImage("home", "桌面设置-2.png", 100);
    // 搜索结果
   adbSystem->clickScreen(503, H_SETTING_SEARCH_Y/*1094*/, 1000);
   adbSystem->cutAnImage("home", "桌面设置-3.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::homeMenu(){
   adbSystem->returnHome();

   adbSystem->clickScreen(79, 2110, 100);

    //菜单下拉.json begin:
    // 下滑屏幕
   adbSystem->swipeScreen(707, 32, 599, 1225, 500);
    // 下滑屏幕2
   adbSystem->swipeScreen(632, 281, 701, 1101, 500);
   adbSystem->cutAnImage("home", "桌面下拉菜单.png", 100);
    // 编辑
   adbSystem->clickScreen(740, 65, 500);
   adbSystem->cutAnImage("home", "桌面下拉菜单-编辑.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::homeLock(){
   adbSystem->returnHome();
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);

    // 长按
  adbSystem->clickLongTime(989, 1699, 1000);
   adbSystem->clickScreen(411, 1822, 500);
   adbSystem->swipeScreen(1004, 1914, 351, 1966, 500);
   adbSystem->swipeScreen(935, 1910, 355, 1960, 500);
   adbSystem->cutAnImage("home", "一键优化.png", 100);

   adbSystem->swipeScreen(908, 1917, 131, 1943, 500);
   adbSystem->swipeScreen(935, 1910, 355, 1960, 500);
   adbSystem->cutAnImage("home", "一键锁屏.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::homeVolume(){
   adbSystem->returnHome();

   adbSystem->clickScreen(79, 2110, 100);
    // 重启主题
   adbSystem->restartActvity("com.android.contacts/.activities.PeopleActivity");

    // -音量
    adbSystem->delVolumes();
    adbSystem->delVolumes();
    adbSystem->delVolumes();

   adbSystem->cutAnImage("home", "音量弹框-1.png", 100);
    // 点击按钮
    adbSystem->delVolumes();
   adbSystem->clickScreen(362, 308, 500);
   adbSystem->cutAnImage("home", "音量弹框-2.png", 100);
   adbSystem->clickScreen(362, 308, 500);

   adbSystem->returnHome();
}

void HuaWeiPhones8::homeNetwork()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);

    // 下滑屏幕
   adbSystem->swipeScreen(707, 32, 599, 1225, 500);
    // 移动网络.png
   adbSystem->clickLongTime(562, 250, 800);
   adbSystem->cutAnImage("home", "移动网络.png", 100);

   adbSystem->returnHome();
}

void HuaWeiPhones8::homePower()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 下滑屏幕
   adbSystem->swipeScreen(721, 42, 723, 920, 500);
    // 下滑屏幕2
   adbSystem->swipeScreen(605, 232, 605, 1107, 500);
    // 超级省电
   adbSystem->clickScreen(954, 642, 500);
    // 应用
   adbSystem->clickScreen(786, 2035, 500);
   adbSystem->cutAnImage("home", "超级省电.png", 100);
    // 退出
   adbSystem->clickScreen(961, 150, 500);
    // 确认
   adbSystem->clickScreen(744, 2015, 500);

   adbSystem->returnHome();
}

void HuaWeiPhones8::homeSimpleMode()
{
   adbSystem->returnHome();
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    //简易模式.json begin:
    //returnHome();
    // 右滑屏幕
   adbSystem->swipeScreen(938, 1098, 214, 1039, 500);
    // 设置
   adbSystem->clickScreen(555, 218, 500);

    // 下滑屏幕
   adbSystem->swipeScreen(503, 1912, 470, 718, 500);
    // 系统
   adbSystem->clickScreen(405, 2081, 500);
    // 简易模式
   adbSystem->clickScreen(747, 1052, 500);
    // 应用
   adbSystem->clickScreen(513, 2068, 1500);
    // 左滑屏幕
    //swipeScreen(13, 1707, 0, 1704, 500);
   adbSystem->swipeScreen(990, 1835, 210, 1832, 500);
    //clickScreen(23, 1851, 500);
    // 其他
   adbSystem->clickScreen(309, 1491, 500);
   adbSystem->cutAnImage("home", "简易模式-其他.png", 100);
    // 返回
   adbSystem->clickScreen(72, 137, 500);
    // 添加
   adbSystem->clickScreen(813, 1055, 500);
   adbSystem->cutAnImage("home", "简易模式-添加.png", 100);
    // 点空白
   adbSystem->clickScreen(437, 1402, 500);
    // 下载
   adbSystem->clickScreen(767, 1573, 500);
   adbSystem->cutAnImage("home", "简易模式-下载.png", 100);
    // 返回
   adbSystem->clickScreen(95, 150, 500);
    // 添加
   adbSystem->clickScreen(928, 1029, 500);
    // 应用
   adbSystem->clickScreen(773, 1910, 500);
   adbSystem->cutAnImage("home", "简易模式-应用.png", 100);

    // 退出简易模式
   adbSystem->returnHome();
   adbSystem->returnHome();
    // 滑动
   adbSystem->swipeScreen(938, 1098, 214, 1039, 500);

    // 设置
   adbSystem->clickScreen(797, 704, 500);
    // 桌面风格
   adbSystem->clickScreen(541, 1214, 500);
    // 退出
   adbSystem->clickScreen(513, 1144, 500);

   adbSystem->returnHome();
}


//**********************************************
// message

void HuaWeiPhones8::messageList(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 列表
   adbSystem->cutAnImage("message", "列表-1.png", 100);

    // 列表-2.png
   adbSystem->swipeScreen(500, 1080, 500, 500, 10);
    // 列表
   adbSystem->cutAnImage("message", "列表-2.png", 100);


   adbSystem->returnHome();
}
void HuaWeiPhones8::messageWebsit(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    // 恶意网站
    // 输入栏
   adbSystem->clickScreen(332, 262, 500);
    //
    adbSystem->inputText("15122139813");
    // 第一条短信
   adbSystem->clickScreen(424, 416, 500);

   adbSystem->cutAnImage("message", "恶意网址.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::messageSetting(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    /// 短信设置
    // 更多
   adbSystem->clickScreen(638, 2071, 500);
    // 设置
   adbSystem->clickScreen(694, 1946, 500);
    // 智能短信服务
   adbSystem->clickScreen(701, M_SETTING_SERVICES_Y/*282*/, 500);// 前移
   adbSystem->cutAnImage("message", "设置-智能短信服务.png", 100);
    // 返回
   adbSystem->clickScreen(82, 147, 500);
    // 高级
   adbSystem->clickScreen(490, M_SETTING_GAOJI_Y/*1224*/, 500);
    // 常用短语
   adbSystem->clickScreen(642, M_SETTING_OFTEN_Y/*301*/, 500);
   adbSystem->cutAnImage("message", "设置-常用短语.png", 100);
    // 返回
   adbSystem->clickScreen(75, 140, 500);
    // 签名
   adbSystem->clickScreen(352, M_SETTING_MARK_Y/*449*/, 500);
   adbSystem->cutAnImage("message", "设置-签名.png", 100);
    // 短信中心 无sim卡
   adbSystem->clickScreen(88, M_SETTING_CENTRE_Y/*150*/, 500);
   adbSystem->cutAnImage("message", "设置-卡2短信中心.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::messagePress(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 长按短信
    // 长按
   adbSystem->clickLongTime(862, 766, 1000);
   adbSystem->cutAnImage("message", "长按短信-1.png", 100);
    // X
   adbSystem->clickScreen(79, 134, 500);
    // 输入
   adbSystem->clickScreen(332, 262, 500);
    adbSystem->inputText("1850036");
    // 第一条短信
   adbSystem->clickScreen(424, 416, 500);
    // 长按
   adbSystem->clickLongTime(752, 1320, 1000);
   adbSystem->cutAnImage("message", "长按短信-2.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::messageNew(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 新建信息

    // 新建
   adbSystem->clickScreen(414, 2071, 500);
   adbSystem->cutAnImage("message", "新建-1.png", 100);
    // 输入1553351250
   adbSystem->clickScreen(217, 294, 500);
    //
   adbSystem->inputText("1553351251");

   adbSystem->clickScreen(400, KEYBORDPOS_Y - 120, 800, NO_CONV_POS);

   adbSystem->inputText("ww");

   adbSystem->cutAnImage("message", "新建-2.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::messageSearch(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索
    // 输入栏
   adbSystem->clickScreen(332, 262, 500);

    // 1
   adbSystem->inputText("1");
   adbSystem->cutAnImage("message", "搜索-2.png", 100);

   adbSystem->delTexts(2);
   adbSystem->inputText("w");

   adbSystem->cutAnImage("message", "搜索-1.png", 100);
   adbSystem->returnHome();
}
void HuaWeiPhones8::messageCollection(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    // 更多
   adbSystem->clickScreen(645, 2074, 500);
    // 我的收藏
   adbSystem->clickScreen(714, 1465, 500);
   adbSystem->cutAnImage("message", "我的收藏.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::messageNotice(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");
    // 输入栏
   adbSystem->clickScreen(332, 262, 500);
    //
   adbSystem->inputText("10010");
    // 第一条短信
   adbSystem->clickScreen(424, 416, 500);

   adbSystem->cutAnImage("message", "联通通知-1.png", 100);
    // 联通通知-2.png

   adbSystem->returnHome();
}
void HuaWeiPhones8::messageRailway(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    // 输入栏
   adbSystem->clickScreen(332, 262, 500);
    //
   adbSystem->inputText("12306");
    // 第一条短信
   adbSystem->clickScreen(424, 416, 500);

   adbSystem->cutAnImage("message", "铁路客服.png", 100);

   adbSystem->returnHome();
}
void HuaWeiPhones8::messageReports(){
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    // 输入栏
   adbSystem->clickScreen(332, 262, 500);
   adbSystem->inputText("1850036");
    // 第一条短信
   adbSystem->clickScreen(424, 416, 500);
    // 长按
   adbSystem->clickLongTime(752, 1317, 1000);
    // 小的更多
   adbSystem->clickScreen(875, M_PRESS_LITTLE_Y/*1130*/, 500);
    // 大的更多
   adbSystem->clickScreen(939, 2053, 500);
    // 查看报告
   adbSystem->clickScreen(872, 1931, 500);
    // 截图
   adbSystem->cutAnImage("message", "查看报告.png", 100);
    // 查看报告.png
   adbSystem->returnHome();
}

void HuaWeiPhones8::messageNavbar()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    // 1条短信
   adbSystem->clickScreen(414, 740, 500);
    // +
   adbSystem->clickScreen(85, 2084, 500);
   adbSystem->cutAnImage("message", "导航栏-1.png", 100);
    // 表情
   adbSystem->clickScreen(862, 1402, 500);
   adbSystem->cutAnImage("message", "导航栏-2.png", 100);

   adbSystem->returnHome();
}

void HuaWeiPhones8::messageSend()
{
   adbSystem->returnHome();
   adbSystem->clickScreen(79, 2110, 100);
    // 重启短信
   adbSystem->restartActvity("com.android.mms/.ui.ConversationList");

    // 搜索号码
   adbSystem->clickScreen(272, 296, 500);
    // 15122139813
   adbSystem->inputText("1512213");
    // 第一条短信
   adbSystem->clickScreen(424, 416, 500);
   adbSystem->cutAnImage("message", "发送短信-1.png", 100);
    // 输入框
   adbSystem->clickScreen(700, 2087, 500);
   adbSystem->cutAnImage("message", "发送短信-2.png", 100);

    adbSystem->delTextTens();
    // 导航栏
   adbSystem->swipeScreen(714, 2143, 698, 1815, 500);
   adbSystem->cutAnImage("message", "发送短信-3.png", 100);
    // 输入happy
   adbSystem->inputText("HAPPY");

   adbSystem->cutAnImage("message", "发送短信-4.png", 100);
    // 关闭导航栏
   adbSystem->clickScreen(102, 2087, 500);
   adbSystem->cutAnImage("message", "发送短信-5.png", 100);
    // 关闭键盘
   adbSystem->clickScreen(296, 1189, 500);
    // 打开导航栏
   adbSystem->swipeScreen(1020, 2141, 1027, 488, 500);
   adbSystem->cutAnImage("message", "发送短信-6.png", 100);

    adbSystem->delTextTens();

   adbSystem->returnHome();
}





void HuaWeiPhones8::init()
{
    ScreenSizeT t;
    t.width = 1080;
    t.height = 2160;
    adbSystem->setBaseScreenSize(t);

    adbSystem->setPhoneScreenSize(phoneCharacters.wm_size);

    qCritical() << "base:" << adbSystem->getBaseSize().width;
    qCritical() << "wm:" << adbSystem->getPhoneSize().height;
}

void HuaWeiPhones8::test()
{
    qDebug() << KEYBORDPOS_X;
    qDebug() << KEYBORDPOS_Y; //no use

    qDebug() << IS_CHECK_KEYBORD;
    qDebug() << SINGAL_KB_SOP_Y ;//add
    /*<!--联系人：  新建{电话输入 添加群组 添加更多} 群组 设置关于 领英！导入导出{从其他设备导入 分享联系人{导入到卡1}}-->*/
    qDebug() << C_NEW_CALL_Y;
    qDebug() << C_NEW_ADDGROUP_Y;
    qDebug() << C_NEW_ADDMORE_Y ;
    qDebug() << C_GROUP_Y;
    qDebug() << C_SETTING_ABOUT_Y ;
    qDebug() << C_LINKIN_Y ;
    qDebug() << C_IEMP_OTHERS_Y ;
    qDebug() << C_IEMP_TOSIM1_Y ;
  /*<!-- dial：设置{更多 通话记录 来电拒绝[页码]} !-->*/
    qDebug() << D_SETTING_MORE_Y;// no use
    qDebug() << D_SETTING_MORE_PAGE;//no use
    qDebug() << D_SETTING_RECORD_Y;
    qDebug() << D_SETTING_RECORD_PAGE ;
    qDebug() << D_SETTING_REJECT_Y ;
    qDebug() << D_SETTING_REJECT_PAGE;

    qDebug() << H_FOLDER_ADD_X ;
    qDebug() << H_FOLDER_ADD_Y ;
    qDebug() << H_SETTING_SEARCH_Y ;//change

    qDebug() << M_SETTING_SERVICES_Y ;
    qDebug() << M_SETTING_GAOJI_Y ;
    qDebug() << M_SETTING_OFTEN_Y ;
    qDebug() << M_SETTING_MARK_Y ;
    qDebug() << M_SETTING_CENTRE_Y ;
    qDebug() << M_PRESS_LITTLE_Y ;
    qDebug() << ocrToken;
}

void HuaWeiPhones8::initPosition()
{
    QFile file("huawei8.xml");
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << "huawei8.xml is not exit";
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
            qDebug() << n.tagName() << n.attribute("id");// << de.attribute("time");// 获取标签属性 名称

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
                    if(de.nodeName() == "s_board_check"){
                        IS_CHECK_KEYBORD = (de.toElement().text().toInt() == 0);
                    }
                    if(de.nodeName() == "s_board_open_y"){
                        SINGAL_KB_SOP_Y = de.toElement().text().toInt();
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
                    if(de.nodeName() == "d_set_more_y"){
                        //D_SETTING_MORE_PAGE = de.attribute("page")[0];
                        D_SETTING_MORE_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "d_set_record_y"){
                        //D_SETTING_RECORD_PAGE = de.attribute("page")[0];
                        D_SETTING_RECORD_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "d_set_callR_y"){
                        //D_SETTING_REJECT_PAGE = de.attribute("page")[0];
                        D_SETTING_REJECT_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "h_folder_add_x"){
                        H_FOLDER_ADD_X = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "h_folder_add_y"){
                        H_FOLDER_ADD_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "h_set_search_y"){
                        H_SETTING_SEARCH_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_set_services_y"){
                        M_SETTING_SERVICES_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_set_gaoji_y"){
                        M_SETTING_GAOJI_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_set_often_y"){
                        M_SETTING_OFTEN_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_set_mark_y"){
                        M_SETTING_MARK_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_set_centre_y"){
                        M_SETTING_CENTRE_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "m_press_little_y"){
                        M_PRESS_LITTLE_Y = de.toElement().text().toInt();
                    }
                    if(de.nodeName() == "ocr_token"){
                        ocrToken = de.toElement().text();
                    }

                }

                break;
            }

        }

        node = node.nextSibling();//与nextSiblingElement差不多
    }
}
