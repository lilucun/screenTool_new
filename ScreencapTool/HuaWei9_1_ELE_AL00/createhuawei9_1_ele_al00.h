#ifndef CREATEHUAWWI9_1_ELE_AL00
#define CREATEHUAWWI9_1_ELE_AL00

#include "phonecreatemanage.h"
class CreateHuaWei9_1_ELE_AL00:public PhoneCreateManage
{
public:
    CreateHuaWei9_1_ELE_AL00();
    ~CreateHuaWei9_1_ELE_AL00();
    ScreenTool* createPhone(const QString &iSerial, const QString &iMenufest);

    const QString serialId();

    QHash<QString , int>* taskIdInfo();
};

#endif // CREATEHUAWWI9_1_ELE_AL00
