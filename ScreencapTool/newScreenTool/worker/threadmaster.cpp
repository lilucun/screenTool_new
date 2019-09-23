#include "threadmaster.h"

#include "devicesmanager.h"
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QTimer>
#include "phones.h"
#include "getphoneobject.h"
#include "QHash"
#include <QStringList>
//#include <assert.h>
#include <QDir>


// 功能： 把新连接的手机的对应线程加入管理队列
// 包含初始化
void ThreadMaster::addThreadPhone(Phones *phone)
{
    // 遍历查询是否存在手机
    foreach (TaskWorker *temp, workList) {
        if (temp->taskInfo.serial == phone->getPhoneSerial()) // 手机的线程已存在
            return;
       }
    TaskWorker *work = new TaskWorker;
    work->copyData(phone);

    this->workList.append(work);
}


// 功能： 把手机从对应线程队列里移除
void ThreadMaster::delThreadPhone(const QString &serial)
{
    // 遍历查询是否存在手机
    foreach (TaskWorker *temp, workList) {
        if (temp->taskInfo.serial == serial) {
            if (temp->isRunning()) {
                temp->terminate();
                temp->wait();
                temp->postTaskResults(temp->taskInfo.taskId, TaskWorker::FAILED, "phone is outline...");// error
            }

            workList.removeOne(temp);
            delete temp;
        }
    }
}

// 清除所有手机
void ThreadMaster::delAllThreadPhone()
{
    foreach (TaskWorker *temp, workList) {

        // 从devices列表内移除 phone
        //emit removePhoneFromDevList(temp->taskInfo.serial);
        workList.removeOne(temp);
        temp->m_stop = true;
        temp->terminate();
        temp->wait();

        delete temp;// 析构函数删除了临时文件
    }
}


// 功能： 判断serial是否在线程列表内
bool ThreadMaster::isWorkListContainsPhone(const QString &serial)
{
    if(serial.isEmpty())
        return false;

    foreach (TaskWorker *work, workList) {
        if (work->taskInfo.serial == serial)
            return true;
    }

    return false;
}

bool ThreadMaster::isThreadPhoneWork(const QString &serial)
{
    if(serial.isEmpty())
        return true;

    foreach (TaskWorker *work, workList) {
        if (work->taskInfo.serial == serial
                && work->taskInfo.phone->getPhoneStatues() == Phones::devReady) {
            return false;
        }
    }

    return true;
}

void ThreadMaster::stopThread(const QString &serial)
{
    foreach (TaskWorker* work, workList) {
        //assert(work->isRunning() == true);// 线程工作，我调用run函数了
        if (work->taskInfo.serial == serial && work->isRunning()) {
            // 保存状态
            //work->m_stop = true;
            work->terminate();
            work->wait();
        }
    }
}

int ThreadMaster::getTaskProcess(const QString &serial)
{
    foreach (TaskWorker* work, workList) {
        if (work->taskInfo.serial == serial)
            return work->taskInfo.taskProcessId;

    }

    return -1;// 不存在该线程
}

int ThreadMaster::getTaskListVersion(const QString &serial)
{
    foreach (TaskWorker* work, workList) {
        if (work->taskInfo.serial == serial) {
            qCritical() << "task version:" << work->taskInfo.taskListVersion;
            return work->taskInfo.taskListVersion;
        }
    }
    
    return 0;
}

void ThreadMaster::updateMasterThreadPhone()
{
    QList<Phones*> tempList = DevicesManager::PhoneList;
    foreach (Phones* tool, tempList) {
        if (!isWorkListContainsPhone(tool->getPhoneSerial())) // 如果这个手机不在线程列表内，加入手机
            addThreadPhone(tool);
    }
}



ThreadMaster::ThreadMaster(QObject *parent) : QObject(parent)
{

    hardwareAddr = DevicesManager::getHostMacAddress();

    tcpIsConn = false;
    socket = new QTcpSocket(this);

    masterHttp = new QNetworkAccessManager(this);

    connect(masterHttp, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    connect(this, SIGNAL(startWorkThreadSig(const QString&)), this, SLOT(startWorkThreadSlot(const QString &)));


    connect(socket, SIGNAL(readyRead()), this, SLOT(readTcpTask()));
    connect(socket, &QTcpSocket::disconnected, [=](){
        reConnTimer->start(10000);
    });


    connectServer();


    connect(this, &ThreadMaster::phoneWorkError, [=](const QString &serial , int taskId, const QByteArray &err_str){
        // 上报结果
        qCritical() << "phone work error " << serial;
        foreach (TaskWorker* work, workList) {
            if (work->taskInfo.serial == serial)
                work->postTaskResults(taskId, TaskWorker::FAILED, err_str);// error

        }

    });

    reConnTimer = new QTimer(this);
    connect(reConnTimer, &QTimer::timeout, [=](){
        qDebug() << "conn server";
        tcpIsConn = false;
        socket->disconnectFromHost();

        connectServer();
//        emit showTcpConn(false);
    });

    reConnTimer->start(10000);

    connect(socket, &QTcpSocket::connected, this, [=](){

        tcpIsConn = true;
        qDebug() << "tcp connected--------------------------";
        reConnTimer->stop();
        if(!taskScyen->isActive())
            taskScyen->start(1000);

        emit showTcpConn(true);
    });

    // 任务队列扫描
    taskScyen = new QTimer(this);
    connect(taskScyen, &QTimer::timeout, [=](){
       //
        if(!taskQueue.isEmpty()) {
           taskScyen->stop();// 暂停扫描

           TaskInfo info = taskQueue.dequeue();

           tempInfo.taskId = info.taskId;
           tempInfo.serial = info.serial;

           getTaskInfo(info.taskId);

        }

    });
    taskScyen->start(1000);

}

ThreadMaster::~ThreadMaster()
{
    qDebug("delete master");

    delAllThreadPhone();
    delTaskList();

}

// 连接服务器
void ThreadMaster::connectServer()
{
    if (!tcpIsConn) {
        socket->connectToHost(IP_ADDR, PORT);
        socket->waitForConnected(3000);
    } else {
        emit showTcpConn(false);
    }
}

// 读取tcp消息
void ThreadMaster::readTcpTask()
{
    if (tcpIsConn) {
        qint64 ariveLen = socket->bytesAvailable();
        QByteArray data = socket->readAll();
        qDebug() << "data:" << data.toHex().data();

        if (data.size() < ariveLen
                || data.size() <= 0) {
            qCritical() << "data is error";
            return;
        }

        unpackTaskData(data);

    }
}

// 开启线程工作
void ThreadMaster::startWorkThreadSlot(const QString& serial)
{

    foreach (TaskWorker *work, workList) {
        //assert(work->taskInfo.serial == serial.trimmed());// 如果不等于异常
        if (work->taskInfo.serial == serial.trimmed()) {
            if (work->isRunning()) {
                emit phoneWorkError(tempInfo.serial, tempInfo.taskId, "phone is working...");
                return;
            }

            // 初始化信息
            work->taskInfo.appList = tempInfo.appList;
            work->taskInfo.themeUrl = tempInfo.themeUrl;
            work->taskInfo.taskId = tempInfo.taskId;

            work->taskInfo.phone->setPhoneStatues(Phones::devBusy);
            work->downLoadTheme();// 下载主题

            return;
        }
    }
    // 发送一个不存在的设备

    emit phoneWorkError(tempInfo.serial, tempInfo.taskId, "phone uid is unmatched...");
}

// 解析任务详情信息
void ThreadMaster::onFinished(QNetworkReply *reply)
{
    bool taskStatus = false;
    // 读取字节
    QByteArray str = reply->readAll();
    do {
        if (str.isEmpty())
            break;


        qDebug() << "获取任务详情 回复消息" << str;

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "获取任务详情成功";

            // 处理任务详情
            QJsonParseError j_err;
            QJsonDocument doc = QJsonDocument::fromJson(str, &j_err);
            if (j_err.error != QJsonParseError::NoError)
                break;


            QJsonObject info = doc.object();
            if (info.contains("code")) {
                int code = info.value("code").toInt(0);
                if (code != 1)
                    break;

            }
            if (info.contains("result")) {
                QJsonObject res_value = info.value("result").toObject();

                if (res_value.contains("taskId"))
                    tempInfo.taskId = res_value.value("taskId").toInt();

                if (res_value.contains("themeUrl"))
                    tempInfo.themeUrl = res_value.value("themeUrl").toString();

                if (res_value.contains("appList")) {
                    // 确保TaskList 被初始化了
                    if (TaskList.isEmpty())
                        break;

                    QHash<QString, int> *temp_appList = TaskList.value(getTaskListVersion(tempInfo.serial));// 获取列表
                    qDebug() << "get taskList:" << temp_appList;
                    if (temp_appList == NULL) {
                        break;
                    }

                    QString str_t = res_value.value("appList").toString();
                    QStringList list = str_t.split(',');

                    if (!tempInfo.appList.isEmpty())
                        tempInfo.appList.clear();

                    for (int i = 0; i < list.size(); ++i) {
                        if(temp_appList->contains(list[i].trimmed())) {
                            tempInfo.appList.append(temp_appList->value(list[i]));
                        } else {
                            qCritical() << "no contains appList:" << list[i];
                        }
                    }
                }

                taskStatus = true;
            }

        } else {
            qCritical() <<"获取任务详情错误";
        }

    } while (0);



    if (taskStatus) {
        this->startWorkThreadSlot(tempInfo.serial);
    } else {
        emit phoneWorkError(tempInfo.serial, tempInfo.taskId, "get task info failed...");
    }

    taskScyen->start(1000);// 开始扫描

    reply->deleteLater();
}

// 心跳
void ThreadMaster::onHeartTimerUp()
{
    if (tcpIsConn) {
        int len = packagetHeadInfo(HeartBeat, 0);

        char buf[48] = "";
        memcpy(buf, &packageHead, len);
        socket->write(buf, len);
    }
}

// 设备断开
void ThreadMaster::devDisConnSlot(const QString &serial, int status)
{
    if(status == 1) {
         delThreadPhone(serial);
    } else {
        // 如果在工作，停止工作
        foreach (TaskWorker *work, workList) {
            if (work->taskInfo.serial == serial) {
                if (work->isRunning()) {
                    work->terminate();
                    work->wait();
                    work->postTaskResults(work->taskInfo.taskId, TaskWorker::FAILED, "phone is outline...");// error
                }
            }
        }
    }
}


// 解析tcp数据

void ThreadMaster::unpackTaskData(QByteArray data)
{

    if (data[0] == '#' && data[1] == '#') {
        if (data[2] != HeartBeat)
            emit showTcpData(data.toHex().data());

        switch(data[2]) {
        case PostTask:
        {
            // 必须按位与
            int dataLen =  (data[4] & 0xFF);
            dataLen |=  ((data[3] << 8)& 0xFF00) ;

            qDebug() << "dataLen:" << dataLen;

            if (dataLen < 4 || dataLen > 20) {
                data[2] == RefuseTask;
                break;
            }

            int taskId = data[8] & 0xff;
            taskId |= ((data[7] << 8) &0xff00);
            taskId |= ((data[6] << 16) & 0xff0000);
            taskId |= ((data[5] << 24) & 0xff000000);

            // 获取serial taskId
            QByteArray temp(data);

            temp = data.right(data.size() - 9);
            if (temp.contains("\r\n"))
                temp = temp.left(temp.size() - 2);

            if (temp.contains("\r"))
                temp = temp.left(temp.size() - 1);


            QString serial(temp);

            qDebug() << serial << " id: " << taskId;

            if (!isThreadPhoneWork(serial)) {
                // 接受任务
                data[2] = AcceptTask;

                // 更新状态1
                setPhoneStatus(serial, Phones::devAcceptTask);

                TaskInfo _list;
                _list.serial = serial;
                _list.taskId = taskId;

                taskQueue.append(_list);

            } else {
                data[2] = RefuseTask;
            }
        }

            socket->write(data);

            break;

        case GetMacAddress:// 返回硬件地址
        {
            char buf[128] = "";
            int headLen = packagetHeadInfo(GetMacAddress, hardwareAddr.size());
            memcpy(buf, &packageHead, sizeof(packageHead));
            memcpy(buf+headLen, hardwareAddr.toStdString().c_str(), hardwareAddr.size());

            socket->write(buf, headLen+hardwareAddr.size());

        }
            break;

        case HeartBeat:
        {

            reConnTimer->start(10000);
        }
            break;
        }
        // 更新手机状态
         qDebug() << "send data:" << data.toHex();
    }
}



// 获取任务详情
bool ThreadMaster::getTaskInfo(const int taskId)
{
    // 获取task信息
    QNetworkRequest request;
    QString url("http://");
    url.append(IP_ADDR);
    url.append(":");
    url.append(QString("%1").arg(HTTP_PORT));
    url.append("/tool/task/info?taskId=");
    url.append(QString::number(taskId));

    qDebug() << url;

    request.setUrl(QUrl(url));
    masterHttp->get(request);

    return true;
}

// 更新手机状态
void ThreadMaster::setPhoneStatus(const QString &serial, int status)
{
    foreach (TaskWorker *work, workList) {
        if (work->taskInfo.serial == serial)
            work->taskInfo.phone->setPhoneStatues(status);
    }
}


// tcp消息头部封装
int ThreadMaster::packagetHeadInfo(unsigned char commendID, int dataLen)
{
    packageHead.symbol1 = '#';
    packageHead.symbol2 = '#';
    packageHead.commond  = commendID;

    packageHead.dataLen[0] = (dataLen >> 8) & 0xFF;
    packageHead.dataLen[1] = dataLen & 0xFF;
    int headLen = sizeof(packageHead)/sizeof(unsigned char);
    return headLen;
}

// 释放任务数据
void ThreadMaster::delTaskList()
{
    for (int i = 0; i < TaskList.size(); ++i) {
        if(TaskList.value(i) != NULL)
            delete TaskList.value(i);
    }
}




















