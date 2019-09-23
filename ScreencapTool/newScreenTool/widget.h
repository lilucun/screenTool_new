#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "phones.h"
#include <QThread>
#include <QHash>
#include <QGraphicsScene>
#include "threadmaster.h"
#include "devicesmanager.h"
#include "getphoneobject.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QGraphicsScene *scene;

    static GetPhoneObject getObject;

    ThreadMaster *masterThread;
    DevicesManager *devManager;

    void initViewGraphics();
    void addDevViewItems(int x, QString text1, QString text2);

    void threadMasterTest();
    void initMasterTaskList();

    void testFunc();
    QTimer *testTimer;

    void delAllItems();
//    void testPhoneCutImages();

    void closeEvent(QCloseEvent *event);
public slots:
    void on_pushButton_clicked();
    void showDevSlot(QHash<QString,QString> &list);
    void onShowTcpConn(bool status);
    void testPhoneCutImages();

    void showTcpData(QByteArray arr);
private slots:
    void on_reconnect_btn_clicked();

    void on_disconnect_btn_clicked();

    void on_addConfig_btn_clicked();

private:
    Ui::Widget *ui;
    QHash<QString, QString> lastDevList;
};


#endif // WIDGET_H
