#include "adbdevices.h"
#include <QApplication>

AdbDevices::AdbDevices()
{
    adbExe = QApplication::applicationDirPath();
    adbExe.append("/plugins/adb/adb.exe devices");
}

QStringList AdbDevices::getDevicesSerials()
{
    //system(adbExe.toStdString().c_str());




}

bool AdbDevices::adbDevices()
{
    if(adbExe.isEmpty())
        return false;

    bool status = false;

    m_out.clear();

    char buf[512]="";
    //adb
    FILE *fp = NULL;

    do{
        fp = popen(adbExe.toStdString().c_str(), "r");
        if(fp == NULL){
            qDebug() << "popen err";
            break;
        }
        // 读取不到结果，说明为空

        while(NULL !=fgets(buf, sizeof(buf), fp)){
            m_out.append(buf);
            memset(buf, 0, sizeof(buf));
        }
        status = true;
    }while(0);
    if(fp != NULL)
        pclose(fp);

    return status;
}

