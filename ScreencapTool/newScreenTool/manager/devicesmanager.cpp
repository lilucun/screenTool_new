#include "devicesmanager.h"
#include <QDebug>
#include <QTimer>
#include <stdio.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QNetworkReply>
#include <widget.h>
#include <QNetworkInterface>
#include <assert.h>
#include <QTextCodec>
//extern const QString IP_ADDR;
//extern const int PORT;


QList<Phones*> DevicesManager::PhoneList;

DevicesManager::DevicesManager(QObject *parent):QObject(parent)
{

    lastDevNum = 0;

    http = new QNetworkAccessManager(this);

    time1 = new QTimer(this);
    connect(time1, SIGNAL(timeout()), this, SLOT(devDetectProcress()));
    time1->start(1000*UPDATE_TIME);// 4s

    adbProcess = new AdbProcess;
    hardwareAddress = getHostMacAddress();
    qDebug() << "mac:" <<hardwareAddress;
    connect(adbProcess, SIGNAL(adbResultHandleSig(AdbProcess::ADB_STATUS)), this, SLOT(adbResultHandleSlot(AdbProcess::ADB_STATUS)));

}

DevicesManager::~DevicesManager()
{
    adbProcess->waitForFinished(3000);
    adbProcess->execAdbCommod("", "kill-server");
    adbProcess->waitForFinished(3000);

    clearAllDev();

    killProcess();
    delete adbProcess;

}


void DevicesManager::devDetectProcress()
{
    adbProcess->execAdbCommod("", " devices");
}

void DevicesManager::adbResultHandleSlot(AdbProcess::ADB_STATUS status)
{
    switch (status) {
    case AdbProcess::ADB_SUCESS_EXEC:
    {
        QStringList args = adbProcess->arguments();
        if (args.contains("devices")) {
            QStringList devices = adbProcess->getDevicesSerialFromStdOut();
            if(devices.size() != lastDevNum){
                devList.clear();
                //            qDebug() << devices;
                for(int i = 0; i < devices.size(); ++i)
                {
                    devList.insert(devices[i], devices[i]);// the key is same
                }

                devUpdate();// update ui while devices changes
            }

            // �ϱ��ֻ���Ϣ
            httpUploadDevInfo();

            lastDevNum = devices.size();
//            QProcess::ProcessState s = adbProcess->state();
//            if(s == QProcess::Running)
//                qDebug() << "status:running";
//            else if(s == QProcess::NotRunning)
//                qDebug() << "not running";

        } else if (args.contains("ro.product.brand")) {

            qDebug() << "brand:" <<  adbProcess->getStdOut();

        } else if (args.contains("ifconfig") && args.contains("wlan0")) {

        }
    }

        break;
    case AdbProcess::ADB_ERROR_EXEC:
        qCritical() << "adbProcess ADB_ERROR_EXEC";
        break;
    case AdbProcess::ADB_ERROR_OTHER:
        qCritical() << "adbProcess ADB_ERROR_OTHER";
        break;
    default:
        qCritical() << "adbProcess unknown error";
        break;
    }
}

void DevicesManager::devUpdate()
{
    //    qDebug() << "devsize:" << devList.size() << " phonesize:" << PhoneList.size();

    devSetStatues();//first

    emit showDevSig(devList);
}

void DevicesManager::devSetStatues()
{
    // ���¶Ͽ��豸
    foreach (Phones* tool, PhoneList) {
        QString serial(tool->getPhoneSerial());
        if (!devList.values().contains(serial)) {
            // phone disconnect
            tool->setPhoneStatues(Phones::devDisConn);
            emit devDisConn(serial, 0);//

            //            qDebug() << tool->getPhoneAliveTime();

            //            tool->phoneAliveTimePlusOne();

            //            if(tool->getPhoneAliveTime() < 0) {
            //                //remove phone
            //                emit devDisConn(serial, 1);//
            //                clearDev(serial);
            //            }

        }
    }

    // ������豸
    foreach (QString id, devList.values()) {
        if (PhoneList.size() == 0) { //null
            Phones *tool = Widget::getObject.phoneObject(id);
            if (tool != NULL)
                PhoneList.push_back(tool);
        } else {
            int i = 0;
            // Ѱ���豸�Ƿ����ֻ��б���
            for (; i < PhoneList.size(); i++) {

                if (id == PhoneList[i]->getPhoneSerial()) {
                    // ֻ�е�ǰ״̬��δ���ӣ������³����������б��ڣ��Ÿ���״̬
                    if (Phones::devDisConn == PhoneList[i]->getPhoneStatues()) {
                        PhoneList[i]->setPhoneStatues(Phones::devReady);
                        //                        PhoneList[i]->initPhoneAliveTime();
                    }

                    break;
                }
            }

            // �豸�����ֻ��б���
            // i�����1��
            if( i >= PhoneList.size() && id != PhoneList[--i]->getPhoneSerial()) {
                Phones *tool =  Widget::getObject.phoneObject(id);
                if(tool != NULL)
                    PhoneList.push_back(tool);
            }
        }

    }
}


QString DevicesManager::getHostMacAddress()
{
    QString strMacAddr = "";
    QList<QNetworkInterface> NetList; //��������
    int NetCount = 0; //��������
    int Neti = 0;
    QNetworkInterface thisNet; //��Ҫʹ�õ�����
    NetList = QNetworkInterface::allInterfaces();//��ȡ����������Ϣ
    NetCount = NetList.count(); //ͳ����������
    for (Neti = 0;Neti < NetCount; Neti++) { //������������
        if (NetList[Neti].isValid()) { //�жϸ������Ƿ��ǺϷ�

            QByteArray encodedString = "��������";
            // �������������󣬲���Ϊ��ǰ��ʹ�õı��뷽ʽ
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            // ʹ�ñ��������ó�Ա���� toUnicode ���ת���󣬾Ϳ�������ʾ
            QString str = codec->toUnicode(encodedString);

            if (NetList[Neti].humanReadableName() == str) {
                thisNet = NetList[Neti]; //����������Ϊ��ǰ����
                break;
            }
        }
    }
    strMacAddr = thisNet.hardwareAddress(); //��ȡ��������MAC
    //
    if (!strMacAddr.isEmpty() && strMacAddr.contains(':')) {
        QStringList addrList = strMacAddr.split(':');
        QString temp;
        for(int i = 0; i < addrList.size(); ++i)
            temp.append(addrList[i]);

        strMacAddr = temp;
    }

    return strMacAddr;
}

void DevicesManager::httpUploadDevInfo()
{
    QJsonArray jArr;

    int n = PhoneList.size();
    for (int i = 0; i < n; i++) {
        QJsonObject obj1;
        obj1.insert("brandName", PhoneList[i]->getPhoneMenufest());
        obj1.insert("modelName", PhoneList[i]->getPhoneProduct());
        obj1.insert("modelSerial", PhoneList[i]->getPhoneSerial());
        obj1.insert("modelSystem", PhoneList[i]->getPhoneVersion());
        ScreenSizeT size_wm = PhoneList[i]->getPhoneSize();
        obj1.insert("modelScreenSize", QString("%1x%2").arg(size_wm.width).arg(size_wm.height));
        obj1.insert("modelStatues", PhoneList[i]->getPhoneStatues());
        obj1.insert("mac", hardwareAddress);

        jArr.insert(i, obj1);
    }

    QJsonDocument document;
    document.setArray(jArr);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);

    qDebug() << "upload phone info" << byte_array;


    QNetworkRequest res;
    QString str("http://");
    str.append(IP_ADDR);
    str.append(":");
    str.append(QString("%1").arg(HTTP_PORT));
    str.append("/tool/device/status");
    res.setUrl(QUrl(str));
    res.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));


    QNetworkReply * reply = http->post(res, byte_array);
    connect(reply, &QNetworkReply::readyRead, this, [=](){

        QByteArray httpRecv = reply->readAll();

        QJsonParseError json_error;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(httpRecv, &json_error));
        if (json_error.error != QJsonParseError::NoError)
            qCritical() << "json error!";


        QJsonObject obj2 = jsonDoc.object();
        int ret = obj2.value("code").toInt();
        if (ret == 1) {
            //            qDebug() << "upload devInfo sucess";
        }

        reply->deleteLater();
    });

}



//// �����豸
void DevicesManager::clearAllDev()
{
    int n = PhoneList.size();
    for (int i = 0; i < n; ++i) {
        if(PhoneList[i] != NULL)
            delete PhoneList[i];
    }
}

void DevicesManager::clearDev(const QString &serial)
{
    int n = PhoneList.size();
    for (int i = 0; i < n; ++i) {
        if (PhoneList[i]->getPhoneSerial() == serial) {
            PhoneList.removeOne(PhoneList[i]);
            delete PhoneList[i];
        }
    }
}
///*
void DevicesManager::reConnectPhones()
{
    time1->stop();

    adbProcess->waitForFinished(3000);
    adbProcess->execAdbCommod("", "kill-server");

    adbProcess->waitForFinished(3000);
    adbProcess->execAdbCommod("", "devices");

    adbProcess->waitForFinished(3000);
    time1->start(4000);
}

void DevicesManager::disConnectPhones()
{
    time1->stop();
    adbProcess->execAdbCommod("", "kill-server");

    devList.clear();
    emit showDevSig(devList);

    clearAllDev();
}
//
void DevicesManager::killProcess()
{
    disconnect(adbProcess, 0, 0, 0);
    adbProcess->kill();
}
//*/

