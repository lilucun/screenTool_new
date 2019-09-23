#include "huaweiphones.h"


HuaWeiPhones::HuaWeiPhones(const PhoneCharacters &phoneCharacters):Phones(phoneCharacters)
{
    adbSystem = new AdbSystemHuaWei(phoneCharacters.phoneSerial);
}
