#ifndef HUAWEI9FACTORY_H
#define HUAWEI9FACTORY_H

#include <QObject>
#include "../../newScreenTool/phones/phonesfactory.h"
class HuaWei9Factory : public QObject, PhonesFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lilucun.phonesfactory.plugin")
    // 将该接口注册到Qt的meta-object system
    Q_INTERFACES(PhonesFactory)
public:
    explicit HuaWei9Factory(QObject *parent = nullptr);
    Phones *createPhone(const PhoneCharacters &phoneCharacters)override;
    //const PhoneCharacters initPhoneCharaters(const QString &serialId)override;

    QHash<QString, int>* taskIdInfo()override;
signals:

public slots:
};

#endif // HUAWEI9FACTORY_H
