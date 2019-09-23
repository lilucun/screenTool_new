#ifndef HUAWEI8FACTORY_H
#define HUAWEI8FACTORY_H

#include <QObject>
#include "../../newScreenTool/phones/phonesfactory.h"

class HuaWei8Factory : public QObject, public PhonesFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lilucun.phonesfactory.plugin")
    // 将该接口注册到Qt的meta-object system
    Q_INTERFACES(PhonesFactory)
public:
    explicit HuaWei8Factory(QObject *parent = nullptr);

    Phones *createPhone(const PhoneCharacters &phoneCharacters)override;
    //const PhoneCharacters initPhoneCharaters(const QString &serialId)override;

    QHash<QString, int>* taskIdInfo()override;

signals:

public slots:
};

#endif // HUAWEI8FACTORY_H
