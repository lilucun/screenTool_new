#include "createhuawei8_0_bla_tl00.h"
#include "huawei8_0_bla_tl00.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QHash>
#include <QDebug>

CreateHuaWei8_0_BLA_TL00::CreateHuaWei8_0_BLA_TL00()
{

}

CreateHuaWei8_0_BLA_TL00::~CreateHuaWei8_0_BLA_TL00()
{

}

ScreenTool *CreateHuaWei8_0_BLA_TL00::createPhone(const QString &iMenufest, const QString &iSerial)
{
    return (new HuaWei8_0_BLA_TL00(iMenufest, iSerial));
}

const QString CreateHuaWei8_0_BLA_TL00::serialId()
{
//    return QString("7VV7N17B07000442");
    return QString("6EB0217902005453");
}

const QString CreateHuaWei8_0_BLA_TL00::returnMenufest()
{
     return QString("Huawei");
}

const QString CreateHuaWei8_0_BLA_TL00::returnProduct()
{
     return QString("DUK-AL20");
}

const ScreenSizeT CreateHuaWei8_0_BLA_TL00::returnPhoneSize()
{
    ScreenSizeT size;
    size.height = 1920;
    size.width = 1080;
    return size;
}

const QString CreateHuaWei8_0_BLA_TL00::returnPhoneVersion()
{
    return QString("8.1.0");
}

QHash<QString, int>* CreateHuaWei8_0_BLA_TL00::taskIdInfo()
{
    // 读取文件
    QHash<QString, int> *TaskListHuawei8_0 = new QHash<QString, int>;

    do
    {

        QFile file1("taskcasehuawei8.0.json");
        if(!file1.open(QFile::ReadOnly))
        {
            qDebug() << "file open failed";
            //log->Log("threadmaster.cpp", 309, 4, 0, "initTaskCaseHash open file failed...");
            break;
        }

        QByteArray json8_0 = file1.readAll();
        file1.close();

        QJsonParseError jerr8_0;
        QJsonDocument jdoc8_0 = QJsonDocument::fromJson(json8_0, &jerr8_0);
        if(jerr8_0.error != QJsonParseError::NoError)
        {
            qDebug() << "json err " << jerr8_0.errorString();
            //log->Log("threadmaster.cpp", 321, 4, 0, "jdoc8_0 json err failed...");
           break;
        }

        QJsonArray arr8_0 = jdoc8_0.array();
        for(int i = 0; i < arr8_0.size(); ++i)
        {
            TaskListHuawei8_0->insert(arr8_0[i].toString(), i);
        }

    }while(0);

//    for(int i = 0; i < TaskListHuawei8_0->size(); ++i)
//    {
//        qDebug() << TaskListHuawei8_0->key(i);
//    }
    //assert(!TaskListHuawei8_0->isEmpty());
	
    return TaskListHuawei8_0;
}
