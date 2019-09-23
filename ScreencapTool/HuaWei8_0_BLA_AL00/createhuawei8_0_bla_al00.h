#ifndef CREATEHUAWEI8_0_BLA_AL00
#define CREATEHUAWEI8_0_BLA_AL00

#include "../phonecreatemanage.h"


class CreateHuaWei8_0_BLA_AL00:public QObject, public PhoneCreateManage
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lilucun.phonecreatemanage.plugin")

    // 将该接口注册到Qt的meta-object system
    Q_INTERFACES(PhoneCreateManage)
public:
    CreateHuaWei8_0_BLA_AL00();
    ~CreateHuaWei8_0_BLA_AL00();

    ScreenTool *createPhone(const QString &iMenufest, const QString &iSerial);

    const QString serialId();

    virtual const QString returnMenufest();
    virtual const QString returnProduct();
    virtual const  ScreenSizeT  returnPhoneSize();
    virtual const QString returnPhoneVersion();

    QHash<QString, int> *taskIdInfo();
};

#endif // CREATEHUAWEI8_0_BLA_AL00
