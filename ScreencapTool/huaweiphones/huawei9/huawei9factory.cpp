#include "huawei9factory.h"
#include "huaweiphones9.h"

HuaWei9Factory::HuaWei9Factory(QObject *parent) : QObject(parent)
{

}

Phones *HuaWei9Factory::createPhone(const PhoneCharacters &phoneCharacters)
{
    return (new HuaWeiPhones9(phoneCharacters));
}

QHash<QString, int> *HuaWei9Factory::taskIdInfo()
{
    return nullptr;
}
