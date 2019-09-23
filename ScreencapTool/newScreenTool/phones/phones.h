#ifndef PHONES_H
#define PHONES_H

#include <QObject>

#define SERVER_USE

#ifdef SERVER_USE
const char IP_ADDR[] = "192.168.1.56";// 服务器
const int PORT = 10002;
const int HTTP_PORT = 8091;
#endif
#ifdef SERVER_TEST
const char IP_ADDR[] = "192.168.1.56";
const int PORT = 10001;
const int HTTP_PORT = 8090;
#endif
#ifdef RUIHONG
const char IP_ADDR[] = "10.4.37.96";
const int PORT = 10001;
const int HTTP_PORT = 8090;
#endif
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

class Phones : public QObject
{
    Q_OBJECT
public:

    enum{devConn = 0x01, devDisConn = 0x02, devBusy = 0x03, devReady = 0x04, devAcceptTask = 0x05};
    explicit Phones(QObject *parent = nullptr);
    explicit Phones(const PhoneCharacters& characters);

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


    void initPhoneAliveTime();
    int getPhoneAliveTime();
    void phoneAliveTimePlusOne();

    virtual const QString getPicturePath()=0;

    virtual void initPicPath()=0;

    virtual void taskIdSwitch(int)=0;
    // 主题安装
    virtual void themeInstall()=0;
    // contact部分截图
    virtual void contactCutImage(){}
    // digit部分截图
    virtual void digitCutImage(){}
    // 桌面部分截图
    virtual void homeCutImage(){}
    // 短信部分截图
    virtual void messageCutImage(){}

    virtual void pushThemeToPhone(const QString &)=0;

protected:
    int phoneStatues;
    int phoneAliveTime;// 60*60*8/n 8hours

    PhoneCharacters phoneCharacters;
signals:

public slots:
};

#endif // PHONES_H
