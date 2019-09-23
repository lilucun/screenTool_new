#ifndef GETPHONEOBJECT_H
#define GETPHONEOBJECT_H

#include "phones.h"
#include "xmlreader.h"
#include "phones.h"
// 添加新手机 获取 手机
class GetPhoneObject
{
public:

    // 设备taskList
    enum PhoneVersion{HuaWei8=0, HuaWei9};

    GetPhoneObject();
    ~GetPhoneObject();

    Phones* phoneObject(const QString &iSerial);

    const PhoneCharacters getPhoneCharatersBySerial(const QString &serial);

    QHash<int, QHash<QString, int> *> updateTaskList();
    QMap<QString, PhoneCharacters> phoneMap;

    Phones *pluginAdd(const QString &pluginName, const PhoneCharacters &phoneCharacters, PhoneVersion version);
    int caseProductVersion(const QString &phonePV);

    void initPhoneList();

private:
    QString pluginPath;
    static QHash<int, QHash<QString, int> *> taskList;
    QHash<QString, int> *huawei8_taskList();
    QHash<QString, int> *huawei9_taskList();
    XmlReader reader;

};

#endif // GETPHONEOBJECT_H
