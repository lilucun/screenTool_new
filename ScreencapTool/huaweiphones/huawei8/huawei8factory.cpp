#include "huawei8factory.h"
#include "huaweiphones8.h"
#include <QDebug>

HuaWei8Factory::HuaWei8Factory(QObject *parent) : QObject(parent)
{

}

Phones *HuaWei8Factory::createPhone(const PhoneCharacters &phoneCharacters)
{
    return (new HuaWeiPhones8(phoneCharacters));
}

QHash<QString, int> *HuaWei8Factory::taskIdInfo()
{
    // 读取文件
    QHash<QString, int>* TaskListHuawei8_0 = new QHash<QString, int>;

    do
    {
        QFile file1("taskcasehuawei8.0.json");
        if(!file1.open(QFile::ReadOnly)){
            qDebug() << "file open failed";
            break;
        }

        QByteArray json8_0 = file1.readAll();
        file1.close();

        QJsonParseError jerr8_0;
        QJsonDocument jdoc8_0 = QJsonDocument::fromJson(json8_0, &jerr8_0);
        if(jerr8_0.error != QJsonParseError::NoError) {
           qDebug() << "json err " << jerr8_0.errorString();
           break;
        }

        QJsonArray arr8_0 = jdoc8_0.array();
        for(int i = 0; i < arr8_0.size(); ++i) {
            TaskListHuawei8_0->insert(arr8_0[i].toString(), i);
        }

    }while(0);

    return TaskListHuawei8_0;
}
