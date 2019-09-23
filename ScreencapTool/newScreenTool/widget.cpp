#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QDebug>
#include "devicesmanager.h"
#include <QGraphicsRectItem>
#include <threadmaster.h>
#include "taskworker.h"
#include <QTimer>
#include "assert.h"
#include "getphoneobject.h"
#include <QApplication>
#include "xmlwriter.h"


GetPhoneObject Widget::getObject;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    devManager = new DevicesManager(this);
    connect(devManager, SIGNAL(showDevSig(QHash<QString,QString>&)), this, SLOT(showDevSlot(QHash<QString,QString>&)));

    initViewGraphics();

    masterThread = new ThreadMaster;

    // 设备断开，停止工作
    connect(devManager, &DevicesManager::devDisConn, masterThread, &ThreadMaster::devDisConnSlot);

    initMasterTaskList();

    connect(masterThread, SIGNAL(showTcpData(QByteArray)), this, SLOT(showTcpData(QByteArray)));
    connect(masterThread, SIGNAL(showTcpConn(bool)), this, SLOT(onShowTcpConn(bool)));

    //testFunc();
    ui->label_conn->setText("未连接服务器");
    ui->label_conn->setStyleSheet("font: 75 12pt 'Aharoni';color:red");
    qDebug() << "port:" << HTTP_PORT;

}

Widget::~Widget()
{
    qDebug("delete widget");

    delAllItems();
    delete scene;
    delete masterThread;

    delete devManager;
    delete ui;
    //qApp->quit();
}


void Widget::on_pushButton_clicked()
{
    testPhoneCutImages();
}


void Widget::showDevSlot(QHash<QString, QString> &list)
{
    // update show ui
    if (lastDevList != list) {
        delAllItems();

        int i = 0;
        foreach (QString dev, list.keys()) {
            addDevViewItems(i, dev, list[dev]);
//            qDebug() << "widget show phones:" << dev;
            i++;
        };
        // 更新masterThread 必须确保 phone 已经add到 PhoneList
        masterThread->updateMasterThreadPhone();
    }

    lastDevList = list;
}

void Widget::onShowTcpConn(bool status)
{
    qDebug() << "show";
    if(status){
        ui->label_conn->setText("已连接服务器");
        ui->label_conn->setStyleSheet("font: 75 12pt 'Aharoni';color:green");
    } else {
        ui->label_conn->setText("未连接服务器");
        ui->label_conn->setStyleSheet("font: 75 12pt 'Aharoni';color:red");
    }
}

#if 1
bool isCreate = false;
bool isStartHuaWei9 = false;
bool isStartHuaWei8 = false;
Phones *huawei9 = NULL;
Phones *huawei8 = NULL;
//TaskWorker *hauwei8_work = NULL;
//TaskWorker *huawei9_work = NULL;
int j = 0;
void Widget::testPhoneCutImages()
{

    if (!isCreate) {
        isCreate = true;

        //huawei8 = getObject.phoneObject("HUAWEI: BLA-AL00", "RKK0218305002430");
        //huawei8 = getObject.phoneObject("", "7VV7N17B07000442");
        //huawei9 = getObject.phoneObject("HUAWEI: HMA-AL00", "66J0218C21005830");
        //huawei9 = getObject.phoneObject("", "6EJ4C18614015976");
        //masterThread->addThreadPhone(huawei8);
        //masterThread->addThreadPhone(huawei9);
//        assert(huawei8 != NULL);
        assert(huawei9 != NULL);
        for (int i = 0; i < 12; ++i) {
            //masterThread->workList[0]->taskInfo.appList.append(1);
            //masterThread->workList[0]->taskInfo.appList.append(8);
            //masterThread->workList[0]->taskInfo.appList.append(5);
            //masterThread->workList[0]->taskInfo.appList.append(7);
            //masterThread->workList[0]->taskInfo.appList.append(13);
            //masterThread->workList[0]->taskInfo.appList.append(16);
            //            masterThread->workList[0]->taskInfo.appList.append(18);
            //            masterThread->workList[0]->taskInfo.appList.append(19);
            //masterThread->workList[0]->taskInfo.appList.append(20);
            //            masterThread->workList[0]->taskInfo.appList.append(27);
            masterThread->workList[0]->taskInfo.appList.append(i);
            //masterThread->workList[1]->taskInfo.appList.append(i);

        }
    }

    //    if(!isStartHuaWei8 && !masterThread->workList[1]->isRunning())
    //    {
    //        //isStartHuaWei8 = true;
    //        QString themeFile(QString("./9/%1.hwt").arg(++j));
    //        masterThread->workList[1]->taskInfo.themeName = themeFile;


    //        masterThread->workList[1]->start();
    //        //return;
    //    }

    //    QTime _time = QTime::currentTime().addMSecs(1000);
    //    while(QTime::currentTime() < _time);


    if (!isStartHuaWei9
            && !masterThread->workList[0]->isRunning()) {
        //isStartHuaWei9 = true;
        QString themeFile(QString("./8/%1.hwt").arg(++j));
        masterThread->workList[0]->taskInfo.themeName = themeFile;


        masterThread->workList[0]->start();
    }

    qDebug() << "============ " << masterThread->workList[0]->taskInfo.phone->getPicturePath();
    // qDebug() << "============ " << masterThread->workList[1]->taskInfo.phone->getPicturePath();
}
#endif

void Widget::showTcpData(QByteArray arr)
{
    QString str = ui->textEdit->toPlainText();
    str.append(arr);
    str.append("|");
    ui->textEdit->setText(str);
}




/*
    Graphic View 说明：
    1 scene 是容器，保存items；view 是视图，界面显示item；当 view 的size大于 scene时，没有滑动条
    2 scene、items 坐标体系是中间为（0，0）原点；view 坐标体系是左上角为（0,0）
    3 items 构造函数的使用的坐标体系是相对于 scene 的，三者之间的坐标可以相互转换
*/

void Widget::initViewGraphics()
{
    QRect re = ui->graphicsView->geometry();
    // 原点坐标 矩形宽高
    // 视图大小 大于 场景，才没有滑动条 这里是+5，缩小
    QRect rect(-re.width()/2 + 5, -re.height()/2 + 5, re.width() - 10, re.height() - 10);
    scene = new QGraphicsScene(rect);

    ui->graphicsView->setScene(scene);

}

void Widget::addDevViewItems(int x, QString text1, QString text2)
{
    // 使用的是scene坐标
    QGraphicsRectItem *item = new QGraphicsRectItem(-scene->width()/2, (-scene->height())/2 + 50*x, scene->width(), 50);
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);

    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(211, 215, 207));
    item->setPen(pen);

    scene->addItem(item);

    QGraphicsSimpleTextItem *ui_text1 = new QGraphicsSimpleTextItem(text1);
    //scene->addItem(text);
    ui_text1->moveBy(-scene->width()/2 + 5, (-scene->height())/2 + 50*x + 5);

    QGraphicsSimpleTextItem *ui_text2 = new QGraphicsSimpleTextItem(text2);
    ui_text2->moveBy(-scene->width()/2 + 5, (-scene->height())/2 + 50*x + 25);

    scene->addItem(ui_text1);
    scene->addItem(ui_text2);
}


void Widget::testFunc()
{
    //testPhoneCutImages();

}

void Widget::delAllItems()
{
    QList<QGraphicsItem*> ll = scene->items();
    foreach (QGraphicsItem *t, ll) {
        scene->removeItem(t);
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    //devManager->adbProcess->kill();
}


#if 0
int i =5;
void Widget::threadMasterTest()
{

    if (i == 5) {
        masterThread->connectServer();
        //assert(masterThread->tcpIsConn == true);
        //assert(masterThread->tcpIsConn == false);
        //masterThread->socket->write("hello world");

        //masterThread->unpackTaskData(data);
        //masterThread->getTaskInfo(2);
        QByteArray arr("##\x01\x00\x14\x00\x00\x00\x02RKK0218305002430");
        masterThread->unpackTaskData(arr);

    }

    if (i == 0) {
        assert(i == 0);
        QList<Phones*> tempList = DevicesManager::PhoneList;
        foreach (Phones* tool, tempList) {
            // 测试多个手机
            if(!masterThread->isWorkListContainsPhone(tool->getPhoneSerial()))
                // 如果这个手机不在线程列表内，加入手机
                masterThread->addThreadPhone(tool);
            // 手机的状态是否一致
            //assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devBusy);
            assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devReady);
            //assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devDisConn);
            // 1 是否一个手机对应一个线程
            assert(masterThread->workList.size() == 1);
            // 2 是否可以终止线程
            //masterThread->startWorkThreadSlot(masterThread->workList[0]->taskInfo.serial);// 启动
            //masterThread->stopThread(masterThread->workList[0]->taskInfo.serial);
            // 3 是否记录下任务进度
            masterThread->getTaskProcess(masterThread->workList[0]->taskInfo.serial);
            // 4 是否会相互干扰
            // 移除线程
            masterThread->delThreadPhone(tool->getPhoneSerial());
            //masterThread
            assert(masterThread->workList.size() == 0);
        }
    }
    if (i == 1) {
        assert(i == 1);
        QList<Phones*> tempList =  DevicesManager::PhoneList;
        foreach (Phones* tool, tempList) {
            // 测试多个手机
            if(!masterThread->isWorkListContainsPhone(tool->getPhoneSerial()))
                // 如果这个手机不在线程列表内，加入手机
                masterThread->addThreadPhone(tool);
            // 手机的状态是否一致
            //assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devBusy);
            //assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devReady);
            assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devDisConn);
            // 1 是否一个手机对应一个线程
            assert(masterThread->workList.size() == 1);
            // 2 是否可以终止线程
            //masterThread->startWorkThreadSlot(masterThread->workList[0]->taskInfo.serial);// 启动
            //masterThread->stopThread(masterThread->workList[0]->taskInfo.serial);
            // 3 是否记录下任务进度
            masterThread->getTaskProcess(masterThread->workList[0]->taskInfo.serial);
            // 4 是否会相互干扰
            // 移除线程
            //masterThread->delThreadPhone(tool->getPhoneSerial());
            //masterThread
            //assert(masterThread->workList.size() == 0);
        }
    }

    if (i == 2) {
        //i++;
        QList<Phones*> tempList =  DevicesManager::PhoneList;
        foreach (Phones* tool, tempList) {
            // 测试多个手机
            if(!masterThread->isWorkListContainsPhone(tool->getPhoneSerial()))
                // 如果这个手机不在线程列表内，加入手机
                masterThread->addThreadPhone(tool);
            // 手机的状态是否一致
            //assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devBusy);
            assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devReady);
            //assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devDisConn);
            // 1 是否一个手机对应一个线程
            assert(masterThread->workList.size() == 1);
            for(int i = 0; i < 1; i=i+2)
                masterThread->workList[0]->taskInfo.appList.push_back(i);
            // 2 是否可以终止线程
            masterThread->workList[0]->start();
            //masterThread->startWorkThreadSlot(masterThread->workList[0]->taskInfo.serial);// 启动
            //assert(masterThread->workList[0]->isRunning() == true);
            assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devBusy);
            //masterThread->stopThread(masterThread->workList[0]->taskInfo.serial);
            // 3 是否记录下任务进度
            masterThread->getTaskProcess(masterThread->workList[0]->taskInfo.serial);
            // 4 是否会相互干扰
            // 移除线程
            //masterThread->delThreadPhone(tool->getPhoneSerial());
            //masterThread
            //assert(masterThread->workList.size() == 0);
        }
    }

    if (i == 3) {
        QList<Phones*> tempList =  DevicesManager::PhoneList;
        foreach (Phones* tool, tempList) {
            // 测试多个手机
            if(!masterThread->isWorkListContainsPhone(tool->getPhoneSerial()))
                // 如果这个手机不在线程列表内，加入手机
                masterThread->addThreadPhone(tool);
            // 手机的状态是否一致
            assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devBusy);
            //assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devReady);
            //assert(masterThread->workList[0]->taskInfo.phone->getPhoneStatues() == Phones::devDisConn);
            // 1 是否一个手机对应一个线程
            assert(masterThread->workList.size() == 1);
            // 2 是否可以终止线程
            //masterThread->startWorkThreadSlot(masterThread->workList[0]->taskInfo.serial);// 启动
            masterThread->stopThread(masterThread->workList[0]->taskInfo.serial);
            assert(masterThread->workList[0]->isRunning() == false);
            // 3 是否记录下任务进度
            masterThread->getTaskProcess(masterThread->workList[0]->taskInfo.serial);
            // 4 是否会相互干扰
            // 移除线程
            //masterThread->delThreadPhone(tool->getPhoneSerial());
            //masterThread
            //assert(masterThread->workList.size() == 0);
        }
    }

    i++;
}

#endif

void Widget::initMasterTaskList()
{
    if (masterThread->TaskList.isEmpty())
        masterThread->TaskList = getObject.updateTaskList();

    //assert(masterThread->TaskList.isEmpty() == false);
    for (int i = 0; i < masterThread->TaskList.size(); ++i) {
        qDebug() << "taskList lists:" << masterThread->TaskList[i];
    }
}




void Widget::on_reconnect_btn_clicked()
{
    devManager->reConnectPhones();
}

void Widget::on_disconnect_btn_clicked()
{
//    devManager->disConnectPhones();
}
// 添加手机配置信息
void Widget::on_addConfig_btn_clicked()
{
    XmlWriter *writer = new XmlWriter(this);
    writer->show();

}
