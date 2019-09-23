#include "getphoneobject.h"
#include <QHash>
#include <QDebug>
#include <QPluginLoader>
#include "phonesfactory.h"
#include <QDir>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QApplication>


QHash<int, QHash<QString, int> *> GetPhoneObject::taskList;


GetPhoneObject::GetPhoneObject()
{
    initPhoneList();
}


GetPhoneObject::~GetPhoneObject()
{

}

//
Phones *GetPhoneObject::phoneObject(const QString &iSerial)
{
    if (iSerial.isEmpty()) {
        qCritical() << "iSerial is null";
        return NULL;
    }

    PhoneCharacters charaters = getPhoneCharatersBySerial(iSerial);
    if(charaters.phoneSerial.isEmpty()){
        qCritical() << "phones is not config";
        return NULL;
    }

    QString pluginName;

    QString phonePV(charaters.phoneMenufest);
    phonePV.append(charaters.phoneVersion);
    qDebug() << phonePV;
    int version = caseProductVersion(phonePV);
    qDebug() << version;
    switch (version) {
    case HuaWei9:
        pluginName.append("huawei9.dll");
        return pluginAdd(pluginName, charaters, HuaWei9);
        break;
    case HuaWei8:
        pluginName.append("huawei8.dll");
        return pluginAdd(pluginName, charaters, HuaWei8);
        break;
    default:
        break;
    }

    return NULL;
}

const PhoneCharacters GetPhoneObject::getPhoneCharatersBySerial(const QString &serial)
{
    // 读取xml文件
//    return reader.getPhoneCharater(serial);
    foreach (QString key, phoneMap.keys()) {
        if(key == serial)
            return phoneMap[key];
    }

    return PhoneCharacters();
}


// 更新tasklist
QHash<int, QHash<QString, int>* > GetPhoneObject::updateTaskList()
{
    QHash<int, QHash<QString, int> *> taskList;
    QHash<QString, int> *temp;

    // 添加代码
    temp = huawei8_taskList();
    taskList.insert(HuaWei8, temp);

    temp = huawei9_taskList();
    taskList.insert(HuaWei9, temp);

    return taskList;
}

Phones *GetPhoneObject::pluginAdd(const QString &pluginName, const PhoneCharacters &phoneCharacters, PhoneVersion version)
{
    if (pluginPath.isEmpty()){
        pluginPath.append(qApp->applicationDirPath());
    }

    PhonesFactory *factory = NULL;

    QDir pluginDir(pluginPath);
    pluginDir.cd("plugins");
    pluginDir.cd("phones");
//    QString str(pluginPath);
//    str.append("/plugins/phones/");
//    str.append(pluginName);
//    qDebug() << str;

//    QLibrary lib("ocrTest.dll");
//    qDebug() << "lib ocr:" << lib.load();
    QPluginLoader loader(pluginDir.absoluteFilePath(pluginName));// must be absolutePath nor not used
//    QPluginLoader loader(pluginName);
    QObject *phone = loader.instance();
    qCritical() << "loader phone:" << loader.errorString() << " " <<pluginName;
    if (phone) {
        factory = qobject_cast<PhonesFactory*>(phone);
        if (factory) {
            Phones * tool = factory->createPhone(phoneCharacters);
//            if(!taskList.keys().contains(version)){
//                taskList.insert(version, factory->taskIdInfo());
//            }

            return tool;
        }

    }
    delete phone;

    return NULL;
}

int GetPhoneObject::caseProductVersion(const QString &phonePV)
{
    // 忽略大小写
    if(phonePV.contains("huawei8", Qt::CaseInsensitive)){
        return HuaWei8;
    } else if(phonePV.contains("huawei9", Qt::CaseInsensitive)){
        return HuaWei9;
    } else {
        return -1;
    }

}

void GetPhoneObject::initPhoneList()
{
    XmlReader reader;
    if(reader.readXml("phones.xml"))
        phoneMap = reader.getList();

    foreach (PhoneCharacters c, phoneMap.values()) {
        qDebug() << c.phoneProduct;
    }
}

QHash<QString, int> *GetPhoneObject::huawei8_taskList()
{
    // 读取文件
    QHash<QString, int> *TaskListHuawei8_0 = new QHash<QString, int>;
    do {
        QFile file1("taskcasehuawei8.0.json");
        if (!file1.open(QFile::ReadOnly)) {
            qCritical() << "file open failed";
            break;
        }

        QByteArray json8_0 = file1.readAll();
        file1.close();

        QJsonParseError jerr8_0;
        QJsonDocument jdoc8_0 = QJsonDocument::fromJson(json8_0, &jerr8_0);
        if (jerr8_0.error != QJsonParseError::NoError) {
            qCritical() << "json err " << jerr8_0.errorString();
            break;
        }

        QJsonArray arr8_0 = jdoc8_0.array();
        for (int i = 0; i < arr8_0.size(); ++i)
            TaskListHuawei8_0->insert(arr8_0[i].toString(), i);


    } while (0);

    return TaskListHuawei8_0;
}

QHash<QString, int> *GetPhoneObject::huawei9_taskList()
{
    // 读取文件
    QHash<QString, int>* TaskListHuawei9_1 = new QHash<QString, int>;

    do {
        QFile file2("taskcasehuawei9.1.json");
        if (!file2.open(QFile::ReadOnly)) {
            qCritical() << "file open failed";
            break;
        }

        QByteArray json9_1 = file2.readAll();
        file2.close();

        QJsonParseError jerr9_1;
        QJsonDocument jdoc9_1 = QJsonDocument::fromJson(json9_1, &jerr9_1);
        if (jerr9_1.error != QJsonParseError::NoError) {
            qCritical() << "json err " << jerr9_1.errorString();
            break;
        }

        QJsonArray arr9_1 = jdoc9_1.array();
        for (int i = 0; i < arr9_1.size(); ++i)
            TaskListHuawei9_1->insert(arr9_1[i].toString(), i);

    } while (0);

    return TaskListHuawei9_1;
}




