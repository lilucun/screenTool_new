#ifndef CREATEHUAWEI9_1_HMA_AL00
#define CREATEHUAWEI9_1_HMA_AL00

#include "../phonecreatemanage.h"
class CreateHuaWei9_1_HMA_AL00:public QObject, public PhoneCreateManage
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lilucun.phonecreatemanage.plugin")

    // 将该接口注册到Qt的meta-object system
    Q_INTERFACES(PhoneCreateManage)

public:
    CreateHuaWei9_1_HMA_AL00();
    ~CreateHuaWei9_1_HMA_AL00();
    ScreenTool* createPhone(const QString &iMenufest, const QString &iSerial);

    const QString serialId();

    virtual const QString returnMenufest();
    virtual const QString returnProduct();
    virtual const  ScreenSizeT  returnPhoneSize();
    virtual const QString returnPhoneVersion();


    QHash<QString , int>* taskIdInfo();
};

#endif // CREATEHUAWEI9_1_HMA_AL00
