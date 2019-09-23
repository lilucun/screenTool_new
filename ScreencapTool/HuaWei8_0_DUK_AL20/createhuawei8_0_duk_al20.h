#ifndef CREATEHUAWEI8_0_DUK_AL20
#define CREATEHUAWEI8_0_DUK_AL20

#include "../phonecreatemanage.h"


class CreateHuaWei8_0_DUK_AL20:public QObject,public PhoneCreateManage
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lilucun.phonecreatemanage.plugin")

    // ���ýӿ�ע�ᵽQt��meta-object system
    Q_INTERFACES(PhoneCreateManage)

public:
    CreateHuaWei8_0_DUK_AL20();
    ~CreateHuaWei8_0_DUK_AL20();
    ScreenTool *createPhone(const QString &iMenufest, const QString &iSerial);

    const QString serialId();
    virtual const QString returnMenufest();
    virtual const QString returnProduct();
    virtual const  ScreenSizeT  returnPhoneSize();
    virtual const QString returnPhoneVersion();

    QHash<QString, int>* taskIdInfo();
};

#endif // CREATEHUAWEI8_0_DUK_AL20
