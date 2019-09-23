#ifndef CREATEHUAWEI8_H
#define CREATEHUAWEI8_H

#include <QObject>
#include "phonecreatemanage.h"

class CreateHuaWei8 : public PhoneCreateManage
{
public:
    CreateHuaWei8();

    const PhoneCharacters initPhoneCharaters(const QString &serialId)override;

};

#endif // CREATEHUAWEI8_H
