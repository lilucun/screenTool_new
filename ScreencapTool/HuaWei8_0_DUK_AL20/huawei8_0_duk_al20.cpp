#include "huawei8_0_duk_al20.h"
#include <QTextCodec>
#include "ocrTest.h"
#include <QDebug>


HuaWei8_0_DUK_AL20::HuaWei8_0_DUK_AL20()
{

}

HuaWei8_0_DUK_AL20::HuaWei8_0_DUK_AL20(const QString &menufest, const QString &iSerial):ScreenTool(menufest, iSerial)
{

}
// 获取当前屏幕文字位置
Pos HuaWei8_0_DUK_AL20::getTextPozision(const QString &, const QByteArray &text)
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

void HuaWei8_0_DUK_AL20::totalCutPicture(const QVector<int> &)
{

}

void HuaWei8_0_DUK_AL20::taskIdSwitch(int i)
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


void HuaWei8_0_DUK_AL20::themeInstall()
{
    // 返回home
    returnHome();
    // 关闭导航栏
    clickScreen(76, 2105, 500);
    // 重启主题
    restartActvity("com.huawei.android.thememanager/.HwThemeManagerActivity");
    delayMS(1000);
    // 我的
    clickScreen(977, 2090, 1000);
//    // 上滑动
//    swipeScreen(838, 1933, 838, 500, 1000);
    // 字体恢复
    clickScreen(295, 856, 500);

    clickScreen(344, 725, 500);

    clickScreen(551, 2076, 500);

//    returnBack();
    clickScreen(75, 148, 500);
    clickScreen(75, 148, 500);
//  // 我的主题
    clickScreen(228, 713, 1000);
    // 选中主题
    clickScreen(226, 660, 1000);
    // 应用
    clickScreen(555, 2078, 1000);

    // 不保留 锁屏杂志
    clickScreen(780, 2021, 2000);
    // home
    returnHome();

}



void HuaWei8_0_DUK_AL20::contactCutImage()
{
    contactsList();
    contactsImpExp();
    contactsSetting();
    contactsGroup();
    contactsLinkedIn();
    contactsNew();
}

void HuaWei8_0_DUK_AL20::digitCutImage()
{
    dialDial();
    dialMore();
    dialDetail();
    dialSave();
    dialKeybord();
    dialMark();
}

void HuaWei8_0_DUK_AL20::homeCutImage()
{
    homeHome();
    homeFolder();
    homeList();
    homeSetting();
    homeMenu();
    homeLock();
    homeVolume();

    homeNetwork();
    homePower();
    homeSimpleMode();
}

void HuaWei8_0_DUK_AL20::messageCutImage()
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

    messageNavbar();
    messageSend();
}

void HuaWei8_0_DUK_AL20::pushThemeToPhone(const QString &themeFile)
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

//**********************************************
// contacts
void HuaWei8_0_DUK_AL20::contactsList()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");

    // 联系人点击
    clickScreen(541, 142, 500);
    cutAnImage("contacts", "联系人列表-1.png", 100);
    // 滑动 err

    swipeScreen(598, 1648, 598, 1000, 500);
    //clickScreen(598, 1648, 500);
    cutAnImage("contacts", "联系人列表-4.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::contactsImpExp()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
    clickScreen(511, 146, 500);
    // 更多
    clickScreen(783, 2063, 500);
    // 导入导出
    clickScreen(875, 1758, 500);
    cutAnImage("contacts", "导入导出-导入导出.png", 100);
#if 1
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("contacts/导入导出-导入导出.png", "从其他设备导入");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);// 有卡

    cutAnImage("contacts", "导入导出-从其他设备导入.png", 100);
    // 下一步
    clickScreen(859, 2041, 500);
    cutAnImage("contacts", "导入导出-从其他设备导入-1.png", 100);
    // 返回
    clickScreen(92, 140, 500);
    // 分享联系人
    cutAnImage("..", "temp.png", 100);
    pos = getTextPozision("contacts/导入导出-导入导出.png", "分享联系人");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
    // 选择1个
    clickScreen(974, 531, 500);
    cutAnImage("contacts", "导入导出-导出到卡1-1.png", 100);
#elif
    // 从其他设备导入
    //clickScreen(865, 541, 500); //无卡
    clickScreen(865, 676, 500);// 有卡
    cutAnImage("contacts", "导入导出-从其他设备导入.png", 100);
    // 下一步
    clickScreen(859, 2041, 500);
    cutAnImage("contacts", "导入导出-从其他设备导入-1.png", 100);
    // 返回
    clickScreen(92, 140, 500);
    // 分享联系人
    clickScreen(820, 931, 500);// 卡1
    //clickScreen(820, 1291, 500);
    // 选择1个
    clickScreen(974, 531, 500);
    cutAnImage("contacts", "导入导出-导出到卡1-1.png", 100);

#endif
    returnHome();
}
void HuaWei8_0_DUK_AL20::contactsSetting()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
    clickScreen(529, 133, 500);
    // 更多
    clickScreen(799, 2075, 500);
    // 设置
    clickScreen(915, 1937, 500);
    cutAnImage("contacts", "设置-设置.png", 100);

    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("contacts/设置-设置.png", "关于");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);// 有卡
    // 关于
//    clickScreen(811, 1137, 500);
    cutAnImage("contacts", "设置-关于.png", 100);
    // 滑动屏幕
    swipeScreen(796, 2155, 796, 1500, 800);
    cutAnImage("contacts", "设置-关于-1.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::contactsGroup()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
    clickScreen(560, 138, 500);
    // 群组
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("", "群组");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
//    clickScreen(747, 402, 500);
    // 新建
    clickScreen(431, 2080, 500);
    clickCancelCutImage(328, 1163, 2000, "contacts", "群组-新建.png");
    //cutAnImage("contacts", "群组-新建.png", 100);
    clickScreen(431, 2080, 500);
    //
    inputText("666");

    cutAnImage("contacts", "群组-新建-1.png", 100);


    returnHome();
}
void HuaWei8_0_DUK_AL20::contactsLinkedIn()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
    clickScreen(539, 167, 500);

    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("contacts/联系人列表-1.png", "我");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
    // 我
//    clickScreen(616, 715, 500);
    cutAnImage("contacts", "领英.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::contactsNew()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 联系人
    clickScreen(538, 147, 500);
    // +
    clickScreen(311, 2041, 500);
    cutAnImage("contacts", "新建-新建联系人.png", 100);
    // 头像
    clickScreen(122, 439, 500);
    cutAnImage("contacts", "新建-编辑头像.png", 100);
    // 空白点击
    clickScreen(846, 1567, 500);
    // 电话号码点击

    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("contacts/新建-新建联系人.png", "手机");
    clickScreenNoConverPos(pos.pos_x+500, pos.pos_y, 500);

    inputText("666");
    cutAnImage("contacts", "新建-电话号码.png", 100);
    // 清除输入
//    clickScreen(1006, 621, 500);
    clickScreenNoConverPos(1080-50, pos.pos_y, 500);
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);

    // 手机
//    clickScreen(442, 632, 500);
    cutAnImage("contacts", "新建-手机.png", 100);
    // 空白点击
    clickScreen(846, 1567, 500);
    // 上滑动
//    swipeScreen(500, 800, 500, 500, 500);
    // 收起键盘
    collapseKeyboard();
    // 加入群组
    cutAnImage("..", "temp.png", 100);
    pos = getTextPozision("../temp.png", "加入群组");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);

//    clickScreen(522, 1125, 500);
    cutAnImage("contacts", "新建-新建联系人-加入群组.png", 100);

    // 取消
    clickScreen(73, 174, 500);
    // 添加其他项
//    clickScreen(557, 1226, 500);
    cutAnImage("..", "temp.png", 100);
    pos = getTextPozision("../temp.png", "添加其他项");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
    // 生日
//    clickScreen(458, 1469, 500);
    cutAnImage("..", "temp.png", 100);
    pos = getTextPozision("../temp.png", "生日");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
    // 截取
    cutAnImage("contacts", "新建-新建联系人-添加更多项-日期.png", 100);

    returnHome();
}


//**********************************************
// digit

void HuaWei8_0_DUK_AL20::dialDial()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");

    // 拨号
    clickScreen(175, 127, 500);
     delayMS(500);
    cutAnImage("digit", "拨号盘-1.png", 100);
    // 151
    clickScreen(252, 1278, 100);
    clickScreen(551, 1487, 100);
    clickScreen(232, 1279, 500);
    cutAnImage("digit", "拨号盘-2.png", 100);
    // 1511
    clickScreen(225, 1256, 100);
    clickScreen(567, 1464, 100);
    clickScreen(241, 1279, 100);
    clickScreen(240, 1263, 500);
    cutAnImage("digit", "拨号盘-6.png", 100);


    returnHome();
}
void HuaWei8_0_DUK_AL20::dialMore()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");

    // 拨号
    clickScreen(183, 134, 500);
    // ...
    clickScreen(887, 2044, 500);
    // 设置
    clickScreen(893, 1834, 800);
    // 下滑
//    swipeScreen(638, 500, 638, 2000, 100);
    verticalRollToTop();
    cutAnImage("digit", "更多设置-设置.png", 100);
    // 滑动到底部
//    swipeScreen(638, 2002, 638, 500, 800);
    verticalRollToBottom();
    cutAnImage("digit", "更多设置-设置-1.png", 100);
    // 通话自动录音
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "通话自动录音");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
//    clickScreen(788, 1770, 500);
    cutAnImage("digit", "更多设置-通话自动录音.png", 100);
    // 指定号码
    clickScreen(732, 649, 500);
    cutAnImage("digit", "更多设置-通话自动录音-1.png", 100);
    // 返回
    clickScreen(116, 141, 500);
    // 返回
    clickScreen(96, 167, 500);
    // 来电拒接短信
//    clickScreen(701, 1347, 500);
    cutAnImage("..", "temp.png", 100);
    pos = getTextPozision("../temp.png", "来电拒接短信");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
    cutAnImage("digit", "更多设置-来电拒接短信.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::dialDetail()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");

    // 拨号
    clickScreen(181, 157, 500);
    // 收起键盘
    clickScreen(242, 2043, 500);
    cutAnImage("digit", "详情-收起拨号盘.png", 100);
    // i
    clickScreen(1018, 399, 500);
    cutAnImage("digit", "详情-联系人详情-1.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::dialSave()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 拨号
    clickScreen(183, 176, 1000);
    // 长按第一个号码
    clickLongTime(30, 456, 1500);// 刚好挡住文字
    cutAnImage("digit", "长按保存.png", 100);
    // 保存至已有联系人
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "保存至已有联系人");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
//    clickScreen(536, 970, 500);
    cutAnImage("digit", "长按保存-保存至已有联系人.png", 100);

    returnHome();
}

void HuaWei8_0_DUK_AL20::dialKeybord()
{
    returnHome();
    returnHome();
    clickScreen(79, 2110, 100);

    // 首先从系统设置打开单手键盘
//    restartActvity("com.android.settings/.Settings");
//    startActivity("com.android.settings/.Settings");
    // 右滑屏幕
    swipeScreen(938, 1098, 214, 1039, 500);
    // 设置
    clickScreen(555, 218, 500);
    //delayMS(500);

    verticalRollToBottom();
//    swipeScreen(818, 2033, 818, 300, 700);
    // 系统
    clickScreen(358, 1702, 500);
    // 单手操作
    clickScreen(555, 617, 500);
    // 单手键盘
    clickScreen(555, 429, 500);

    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "单手键盘");
    clickScreenNoConverPos(1080-100, pos.pos_y, 500);
    // 关闭
//    clickScreen(943, 1429, 500);

    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");
    // 拨号
    clickScreen(183, 176, 500);

    // 键盘左上角
    clickScreen(39, 1301, 500);
    // 删除
    clickScreen(684, 2044, 500);
    // 拨号
    clickScreen(183, 176, 500);
    cutAnImage("digit", "单手键盘-1.png", 100);
    // 按住并截图
     // 键盘切到右边
    clickScreen(939, 1664, 500);
    clickScreen(941, 1667, 500);
    cutAnImage("digit", "单手键盘-2.png", 100);

    clickScreen(989, 2044, 500);
    cutAnImage("digit", "单手键盘-3.png", 100);

    returnHome();
    returnHome();
    // 右滑屏幕
    swipeScreen(938, 1098, 214, 1039, 500);
    // 设置
    clickScreen(555, 218, 500);
    //delayMS(500);

    verticalRollToBottom();
//    swipeScreen(818, 2033, 818, 300, 700);
    // 系统
    clickScreen(358, 1702, 500);
    // 单手操作
    clickScreen(555, 617, 500);
    // 单手键盘
    clickScreen(555, 429, 500);
    // 关闭
    clickScreenNoConverPos(1080-100, pos.pos_y, 500);

    returnHome();

}

void HuaWei8_0_DUK_AL20::dialMark()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");

    delayMS(500);
    // 拨号
    clickScreen(183, 176, 1000);
    // 长按第一个号码
    clickLongTime(30, 456, 1500);// 刚好挡住文字
    // 标记为
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "标记为");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
//    clickScreen(457, 694, 500);
    cutAnImage("digit", "标记-标记为.png", 100);

    returnHome();
}

/*******************************************************/
//home

void HuaWei8_0_DUK_AL20::homeHome()
{
    returnHome();
    returnHome();
    clickScreen(79, 2110, 100);

    cutAnImage("home", "桌面-1.png", 100);
    // 左滑屏幕
    swipeScreen(239, 986, 829, 960, 100);
    cutAnImage("home", "桌面-2.png", 100);
    returnHome();
    // 右滑屏幕
    swipeScreen(839, 986, 329, 960, 10);
    cutAnImage("home", "桌面-3.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::homeFolder()
{
    returnHome();
    returnHome();
    clickScreen(79, 2110, 100);

    // 左滑屏幕
    swipeScreen(931, 1029, 309, 1055, 800);
    // 文件夹
    clickScreen(973, 205, 500);
    //cutAnImage("home", "文件夹-4.png", 100);
    //左滑屏幕
    //swipeScreen(849, 1183, 214, 1179, 800);
    swipeHalfCutImage(849, 1183, 555, 1179, "home", "文件夹-4.png");

    swipeScreen(849, 1183, 214, 1179, 500);
    swipeScreen(849, 1183, 214, 1179, 500);
    // +
//    clickScreen(251, 783, 500);
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "添加");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y-100, 500);
    //cutAnImage("home", "文件夹添加.png", 100);
    clickCancelCutImage(305, 2028, 2000, "home", "文件夹添加.png");

    returnHome();
}
void HuaWei8_0_DUK_AL20::homeList()
{
    returnHome();
    returnHome();
    clickScreen(79, 2110, 100);

    // 应用
    clickScreen(543, 2010, 500);
    cutAnImage("home", "应用列表-2.png", 100);
    // J
    clickScreen(1040, 1032, 500);
    cutAnImage("home", "应用列表-3.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::homeSetting(){
    returnHome();
    returnHome();
    clickScreen(79, 2110, 100);

    //设置.json begin:
    // 长按
    clickLongTime(989, 1400, 1500);
    // 设置
    clickScreen(915, 1815, 500);
    cutAnImage("home", "桌面设置-2.png", 100);
    // 搜索结果
//    clickScreen(503, 1094, 1000);
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "搜索结果");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
    cutAnImage("home", "桌面设置-3.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::homeMenu(){
    returnHome();
    clickScreen(79, 2110, 100);

    //菜单下拉.json begin:
    // 下滑屏幕
    swipeScreen(707, 32, 599, 1225, 500);
    // 下滑屏幕2
    swipeScreen(632, 281, 701, 1101, 500);
    cutAnImage("home", "桌面下拉菜单.png", 100);
    // 编辑
    clickScreen(740, 65, 500);
    cutAnImage("home", "桌面下拉菜单-编辑.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::homeLock(){
    returnHome();
    returnHome();
    clickScreen(79, 2110, 100);

    // 长按
   clickLongTime(989, 1400, 1500);
    clickScreen(411, 1822, 500);
    swipeScreen(1004, 1914, 351, 1966, 500);
    swipeScreen(935, 1910, 355, 1960, 500);
    cutAnImage("home", "一键优化.png", 100);

    swipeScreen(908, 1917, 131, 1943, 500);
    swipeScreen(935, 1910, 355, 1960, 500);
    cutAnImage("home", "一键锁屏.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::homeVolume(){
    returnHome();

    clickScreen(79, 2110, 100);
    // 重启主题
    restartActvity("com.android.contacts/.activities.PeopleActivity");

    // -音量
    delVolumes();
    delVolumes();
    delVolumes();

    cutAnImage("home", "音量弹框-1.png", 100);
    // 点击按钮
    delVolumes();
//    clickScreen(362, 308, 500);

    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "静音");
    delVolumes();
    clickScreenNoConverPos(pos.pos_x+100, pos.pos_y, 500);
    cutAnImage("home", "音量弹框-2.png", 100);
//    clickScreen(362, 308, 500);
    delVolumes();
    clickScreenNoConverPos(pos.pos_x+100, pos.pos_y, 500);

    returnHome();
}

void HuaWei8_0_DUK_AL20::homeNetwork()
{
    returnHome();
    clickScreen(79, 2110, 100);

    // 下滑屏幕
    swipeScreen(707, 32, 599, 1225, 500);
    // 移动网络.png
    clickLongTime(562, 250, 1500);
    cutAnImage("home", "移动网络.png", 100);

    returnHome();
}

void HuaWei8_0_DUK_AL20::homePower()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 展开菜单栏
    expandNotifactionFull();

    // 打开设置
//    clickScreen(954, 642, 500);
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "星期");
    clickScreenNoConverPos(1080-150, pos.pos_y-30, 500);

    cutAnImage("..", "temp.png", 100);
    pos = getTextPozision("../temp.png", "电池");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);

    cutAnImage("..", "temp.png", 100);
    pos = getTextPozision("../temp.png", "超级省电");
    clickScreenNoConverPos(1080-150, pos.pos_y, 500);
    // 应用
    clickScreen(786, 2035, 500);
    cutAnImage("home", "超级省电.png", 100);
    // 退出
    clickScreen(961, 150, 500);
    // 确认
    clickScreen(744, 2015, 500);

    returnHome();
}

void HuaWei8_0_DUK_AL20::homeSimpleMode()
{
    returnHome();
    returnHome();
    clickScreen(79, 2110, 100);
    //简易模式.json begin:
    // 右滑屏幕
    swipeScreen(938, 1098, 214, 1039, 500);
    // 设置
    clickScreen(555, 218, 500);

    // 下滑屏幕
    verticalRollToBottom();
    // 系统
    clickScreen(405, 2081, 500);
    // 简易模式
    cutAnImage("..", "temp.png", 100);
    Pos pos = getTextPozision("../temp.png", "简易模式");
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
//    clickScreen(747, 1052, 500);
    // 应用
    clickScreen(513, 2068, 1500);
    // 左滑屏幕
    //swipeScreen(13, 1707, 0, 1704, 500);
    swipeScreen(990, 1835, 210, 1832, 500);
    //clickScreen(23, 1851, 500);
    // 其他
    clickScreen(309, 1491, 500);
    cutAnImage("home", "简易模式-其他.png", 100);
    // 返回
    clickScreen(72, 137, 500);
    // 添加
    clickScreen(813, 1055, 500);
    cutAnImage("home", "简易模式-添加.png", 100);
    // 点空白
    clickScreen(437, 1402, 500);
    // 下载
    clickScreen(767, 1573, 500);
    cutAnImage("home", "简易模式-下载.png", 100);
    // 返回
    clickScreen(95, 150, 500);
    // 添加
    clickScreen(928, 1055, 500);

    // 应用
    clickScreen(773, 1910, 500);
    cutAnImage("home", "简易模式-应用.png", 100);

    // 退出简易模式
    returnHome();
    returnHome();
    // 滑动
    swipeScreen(938, 1098, 214, 1039, 500);
    // 设置
    clickScreen(797, 704, 500);
    // 更多设置
    clickScreen(518, 2094, 500);
    // 下滑
    verticalRollToBottom();
    // 系统
    clickScreen(405, 2081, 500);
    // 简易模式
//    clickScreen(747, 1052, 500);
    clickScreenNoConverPos(pos.pos_x, pos.pos_y, 500);
    // 退出
    clickScreen(513, 2068, 500);

    returnHome();
}


//**********************************************
// message

void HuaWei8_0_DUK_AL20::messageList(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");
    // 列表
    cutAnImage("message", "列表-1.png", 100);

    // 列表-2.png
    swipeScreen(500, 1080, 500, 500, 10);
    // 列表
    cutAnImage("message", "列表-2.png", 100);

    returnHome();
}


void HuaWei8_0_DUK_AL20::messageWebsit(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");

    // 恶意网站
    // 输入栏
//    clickScreen(332, 262, 500);
    clickScreenNoConverPos(332, 262, 500);
    //
    inputText("15122139813");
    // 第一条短信
    clickScreenNoConverPos(424, 416, 500);

    cutAnImage("message", "恶意网址.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::messageSetting(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");

    /// 短信设置
    // 更多
    clickScreen(638, 2071, 500);
    // 设置
    clickScreen(694, 1946, 500);
    // 智能短信服务
    clickScreenNoConverPos(701, 376, 500);// 前移
    cutAnImage("message", "设置-智能短信服务.png", 100);
    // 返回
    clickScreenNoConverPos(82, 147, 500);
    // 高级
    clickScreenNoConverPos(490, 1737, 500);

    // 常用短语
    clickScreenNoConverPos(642, 301, 500);
    cutAnImage("message", "设置-常用短语.png", 100);
    // 返回
    clickScreenNoConverPos(75, 140, 500);
    // 签名
    clickScreenNoConverPos(352, 449, 500);
    cutAnImage("message", "设置-签名.png", 100);
    // 短信中心 无sim卡
    clickScreenNoConverPos(88, 150, 500);
    cutAnImage("message", "设置-卡2短信中心.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::messagePress(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");
    // 长按短信
    // 长按
    clickLongTimeNoConverPos(862, 766, 1500);
    cutAnImage("message", "长按短信-1.png", 100);
    // X
    clickScreenNoConverPos(79, 134, 500);
    // 输入
    clickScreenNoConverPos(332, 262, 500);
    inputText("1850036");
    // 第一条短信
    clickScreenNoConverPos(424, 416, 500);
    // 长按
    clickLongTimeNoConverPos(752, 1320, 1500);
    cutAnImage("message", "长按短信-2.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::messageNew(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");
    // 新建信息

    // 新建
    clickScreen(414, 2071, 500);
    cutAnImage("message", "新建-1.png", 100);
    // 输入1553351250
    clickScreenNoConverPos(217, 294, 500);
    //
    inputText("1553351250");

    cutAnImage("message", "新建-2.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::messageSearch(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");
    // 搜索

    // 输入栏
    clickScreenNoConverPos(332, 262, 500);

    // 1
    inputText("1");
    cutAnImage("message", "搜索-2.png", 100);

    // 删除1
    delTexts(2);

    inputText("我");
    clickScreenNoConverPos(777, 1936, 500);
    clickScreenNoConverPos(79, 1492, 500);
    cutAnImage("message", "搜索-1.png", 100);
    returnHome();
}
void HuaWei8_0_DUK_AL20::messageCollection(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");

    // 更多
    clickScreen(645, 2074, 500);
    // 我的收藏
    clickScreen(714, 1465, 500);
    cutAnImage("message", "我的收藏.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::messageNotice(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");
    // 输入栏
    clickScreenNoConverPos(332, 262, 500);
    //
    inputText("10010");
    // 第一条短信
    clickScreenNoConverPos(424, 416, 500);

    cutAnImage("message", "联通通知-1.png", 100);
    // 联通通知-2.png

    returnHome();
}
void HuaWei8_0_DUK_AL20::messageRailway(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");

    // 输入栏
    clickScreenNoConverPos(332, 262, 500);
    //
    inputText("12306");
    // 第一条短信
    clickScreenNoConverPos(424, 416, 500);

    cutAnImage("message", "铁路客服.png", 100);

    returnHome();
}
void HuaWei8_0_DUK_AL20::messageReports(){
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");

    // 输入栏
    clickScreenNoConverPos(332, 262, 500);
    inputText("1850036");
    // 第一条短信
    clickScreenNoConverPos(424, 416, 500);
    // 长按
    clickLongTimeNoConverPos(752, 1317, 1500);
    // 小的更多
    clickScreenNoConverPos(875, 1130, 500);
    // 大的更多
    clickScreen(939, 2053, 500);
    // 查看报告
    clickScreen(872, 1931, 500);
    // 截图
    cutAnImage("message", "查看报告.png", 100);
    // 查看报告.png
    returnHome();
}

void HuaWei8_0_DUK_AL20::messageNavbar()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");

    // 短信
    //导航栏 json begin:
    // 1条短信
    clickScreenNoConverPos(414, 740, 500);
    // +
    clickScreen(85, 2084, 500);
    cutAnImage("message", "导航栏-1.png", 100);
    // 表情
    clickScreen(862, 1402, 500);
    cutAnImage("message", "导航栏-2.png", 100);

    returnHome();
}

void HuaWei8_0_DUK_AL20::messageSend()
{
    returnHome();
    clickScreen(79, 2110, 100);
    // 重启短信
    restartActvity("com.android.mms/.ui.ConversationList");
    // 发送短信
    // 搜索
    clickScreenNoConverPos(272, 296, 500);
    // 15122139813
    inputText("1512213");
    // 第一条短信
    clickScreenNoConverPos(424, 416, 500);
    cutAnImage("message", "发送短信-1.png", 100);
    // 输入框
    clickScreenNoConverPos(700, 2087, 500);
    cutAnImage("message", "发送短信-2.png", 100);

    delTextTens();
    // 导航栏
    swipeScreen(714, 2143, 698, 1815, 500);
    cutAnImage("message", "发送短信-3.png", 100);
    // 输入happy
    inputText("HAPPY");

    cutAnImage("message", "发送短信-4.png", 100);
    // 关闭导航栏
    clickScreen(102, 2087, 500);
    cutAnImage("message", "发送短信-5.png", 100);
    // 关闭键盘
    collapseKeyboard();
    // 打开导航栏
    swipeScreen(1020, 2141, 1027, 488, 500);
    cutAnImage("message", "发送短信-6.png", 100);

    delTextTens();

    returnHome();
}
