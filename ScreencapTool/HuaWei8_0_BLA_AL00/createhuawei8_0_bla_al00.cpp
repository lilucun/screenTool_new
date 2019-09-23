#include "createhuawei8_0_bla_al00.h"
#include "huawei8_0_bla_al00.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QHash>
#include <QDebug>
#include <assert.h>
CreateHuaWei8_0_BLA_AL00::CreateHuaWei8_0_BLA_AL00()
{

}

CreateHuaWei8_0_BLA_AL00::~CreateHuaWei8_0_BLA_AL00()
{

}

ScreenTool *CreateHuaWei8_0_BLA_AL00::createPhone(const QString &iMenufest, const QString &iSerial)
{
    return (new HuaWei8_0_BLA_AL00(iMenufest, iSerial));
}

const QString CreateHuaWei8_0_BLA_AL00::serialId()
{
    return QString("LKX7N17C23001193");// 本来的
    //return QString("X2P5T15A15000702");
}

const QString CreateHuaWei8_0_BLA_AL00::returnMenufest()
{
     return QString("Huawei");
}

const QString CreateHuaWei8_0_BLA_AL00::returnProduct()
{
     return QString("BLA-AL00");
}

const ScreenSizeT CreateHuaWei8_0_BLA_AL00::returnPhoneSize()
{
    ScreenSizeT size;
    size.height = 2160;
    size.width = 1080;
    return size;
}

const QString CreateHuaWei8_0_BLA_AL00::returnPhoneVersion()
{
    return QString("8.1.0");
}

QHash<QString, int>* CreateHuaWei8_0_BLA_AL00::taskIdInfo()
{
    // 读取文件
    QHash<QString, int> *TaskListHuawei8_0 = new QHash<QString, int>;

    do
    {
        QFile file1("taskcasehuawei8.0.json");
        if(!file1.open(QFile::ReadOnly)) {
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
