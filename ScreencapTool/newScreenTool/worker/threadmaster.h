#ifndef THREADMASTER_H
#define THREADMASTER_H

#include <QObject>
#include <QTcpSocket>
#include "taskworker.h"
#include <QList>
#include <QNetworkAccessManager>
#include <QQueue>

const char PostTask = 0x01;
const char AcceptTask  = 0x02;
const char RefuseTask = 0x03;
const char GetMacAddress  = 0x04;
const char HeartBeat = 0x05;

struct PackageHead
{
    unsigned char symbol1;
    unsigned char symbol2;
    unsigned char commond;
    unsigned char dataLen[2];
};



class ThreadMaster : public QObject
{
    Q_OBJECT
public:
    // QHash<QString, *> error
    QHash<int, QHash<QString, int>*> TaskList;

    explicit ThreadMaster(QObject *parent = nullptr);
    ~ThreadMaster();

    PackageHead packageHead;

    QTcpSocket *socket;
    QNetworkAccessManager *masterHttp;//get taskinfo
    QList<TaskWorker*> workList;
    TaskInfo tempInfo;
    QQueue<TaskInfo> taskQueue;

    QString hardwareAddr;
    QTimer *reConnTimer;
    QTimer *taskScyen;

    bool tcpIsConn;
    void connectServer();

    void unpackTaskData(QByteArray data);

    bool getTaskInfo(const int taskId);

    void setPhoneStatus( const QString &serial ,int status);


    void addThreadPhone(Phones *phone);
    void delThreadPhone(const QString &serial);
    void delAllThreadPhone();
    bool isWorkListContainsPhone(const QString &serial);
    bool isThreadPhoneWork(const QString &serial);

    void stopThread(const QString &serial);
    int getTaskProcess(const QString &serial);
    int getTaskListVersion(const QString &serial);

    void updateMasterThreadPhone();
    int packagetHeadInfo(unsigned char commendID, int dataLen);

    void delTaskList();
signals:
    void startWorkThreadSig(const QString &serial);
    void runStartSig();
    // 移除手机从设备列表 槽在 devicesmansger.cpp内
    void removePhoneFromDevList(const QString &serial);
    void phoneWorkError(const QString &serial, int taskId, const QByteArray &err_str);
    void showTcpData(QByteArray);
    void showTcpConn(bool);

public slots:

    void readTcpTask();

    void startWorkThreadSlot(const QString &serial);
    void onFinished(QNetworkReply*reply);
    void onHeartTimerUp();

    void devDisConnSlot(const QString& serial, int status);
};


#endif // THREADMASTER_H
