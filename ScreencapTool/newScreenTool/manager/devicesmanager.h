#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include "phones.h"
#include "adbprocess.h"


class DevicesManager:public QObject
{
    Q_OBJECT
public:
    explicit DevicesManager(QObject *parent = nullptr);
    ~DevicesManager();

//    static QList<Phones *> getPhoneList();
    static QList<Phones*> PhoneList;

    static QString getHostMacAddress();

    void reConnectPhones();
    void disConnectPhones();
    AdbProcess *adbProcess;
    // add 9.20
    void adbDevices();


    void killProcess();
private:
    QTimer *time1;

    QNetworkAccessManager *http;
    QString hardwareAddress;

    void devUpdate();
    void devSetStatues();
    void httpUploadDevInfo();


   QHash<QString, QString> devList;// save iproduct+imanufecture, iserinumber


    int lastDevNum;

    void clearAllDev();

    void clearDev(const QString &serial);

signals:
    void showDevSig(QHash<QString, QString> &list);
    void devDisConn(const QString &serial, int status);

public slots:
    void devDetectProcress();

    void adbResultHandleSlot(AdbProcess::ADB_STATUS status);
};


#endif // DEVICEMANAGER_H
