#include "createhuawei8_0_duk_al20.h"
#include "huawei8_0_duk_al20.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QHash>
#include <QDebug>

CreateHuaWei8_0_DUK_AL20::CreateHuaWei8_0_DUK_AL20()
{

}

CreateHuaWei8_0_DUK_AL20::~CreateHuaWei8_0_DUK_AL20()
{

}

ScreenTool *CreateHuaWei8_0_DUK_AL20::createPhone(const QString &iMenufest, const QString &iSerial)
{
    return (new HuaWei8_0_DUK_AL20(iMenufest, iSerial));
}

const QString CreateHuaWei8_0_DUK_AL20::serialId()
{
    return QString("6EB0217715006286");
}

const QString CreateHuaWei8_0_DUK_AL20::returnMenufest()
{
     return QString("Huawei");
}

const QString CreateHuaWei8_0_DUK_AL20::returnProduct()
{
     return QString("DUK-AL20");
}

const ScreenSizeT CreateHuaWei8_0_DUK_AL20::returnPhoneSize()
{
    ScreenSizeT size;
    size.height = 1920;
    size.width = 1080;
    return size;
}

const QString CreateHuaWei8_0_DUK_AL20::returnPhoneVersion()
{
    return QString("8.1.0");
}

QHash<QString, int>* CreateHuaWei8_0_DUK_AL20::taskIdInfo()
{
    // 读取文件
    QHash<QString, int>* TaskListHuawei8_0 = new QHash<QString, int>;

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

    return TaskListHuawei8_0;
}
