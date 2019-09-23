#include "createhuawei9_1_ele_al00.h"
#include "huawei9_1_ele_al00.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QHash>
#include <QDebug>

CreateHuaWei9_1_ELE_AL00::CreateHuaWei9_1_ELE_AL00()
{

}

CreateHuaWei9_1_ELE_AL00::~CreateHuaWei9_1_ELE_AL00()
{

}

ScreenTool *CreateHuaWei9_1_ELE_AL00::createPhone(const QString &iMenufest, const QString &iSerial)
{
    return (new HuaWei9_1_ELE_AL00(iMenufest, iSerial));
}

const QString CreateHuaWei9_1_ELE_AL00::serialId()
{
    //return QString("Q5S0219311002934");
    return QString("6EJ4C18614015976");
}

QHash<QString, int> *CreateHuaWei9_1_ELE_AL00::taskIdInfo()
{
    // 读取文件
    QHash<QString, int> *TaskListHuawei9_1 = new QHash<QString, int>;

    do
    {
        QFile file2("taskcasehuawei9.1.json");
        if(!file2.open(QFile::ReadOnly))
        {
            qDebug() << "file open failed";
            //log->Log("threadmaster.cpp", 335, 4, 0, "file2 open failed...");
            break;
        }

        QByteArray json9_1 = file2.readAll();
        file2.close();

        QJsonParseError jerr9_1;
        QJsonDocument jdoc9_1 = QJsonDocument::fromJson(json9_1, &jerr9_1);
        if(jerr9_1.error != QJsonParseError::NoError)
        {
            qDebug() << "json err " << jerr9_1.errorString();
            //log->Log("threadmaster.cpp", 347, 4, 0, "jerr9_1 json err failed...");
            break;
        }

        QJsonArray arr9_1 = jdoc9_1.array();
        for(int i = 0; i < arr9_1.size(); ++i)
        {
            TaskListHuawei9_1->insert(arr9_1[i].toString(), i);
        }
    }while(0);


    return TaskListHuawei9_1;
    //return true;
}
