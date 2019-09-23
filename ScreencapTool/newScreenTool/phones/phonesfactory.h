#ifndef PHONESFACTORY_H
#define PHONESFACTORY_H

#include "phones.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QHash>

class PhonesFactory
{
public:

    explicit PhonesFactory();

    virtual Phones *createPhone(const PhoneCharacters &phoneCharacters)=0;

    //virtual const PhoneCharacters initPhoneCharaters(const QString &serialId)=0;

//    virtual const QString serialId(){}

//    virtual const QString returnMenufest(){}
//    virtual const QString returnProduct(){}
//    virtual const ScreenSizeT returnPhoneSize(){}
//    virtual const QString returnPhoneVersion(){}

    virtual QHash<QString, int>* taskIdInfo()=0;

};

// 插件使用
#define phonesfactory_iid "lilucun.phonesfactory.plugin"
// 说明
Q_DECLARE_INTERFACE(PhonesFactory, phonesfactory_iid)

#endif // PHONESFACTORY_H
