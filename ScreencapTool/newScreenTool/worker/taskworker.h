#ifndef TASKWORKER_H
#define TASKWORKER_H

#include <QObject>
#include <QThread>
#include <QNetworkAccessManager>
#include <QVector>
#include <QFile>
#include "phones.h"
#include <QNetworkReply>
//#include "phonecreatemanage.h"
#include "getphoneobject.h"

struct TaskInfo
{
    QString menufest;
    QString product;
    QString serial;
    QString phoneVersion;
    Phones* phone;

    QString themeUrl;// 主题下载地址
    QString themeName;
    int taskId;//任务id
    GetPhoneObject::PhoneVersion taskListVersion;
    QVector<int> appList;//截图的具体部分
    int taskProcessId;// 记录任务完成的进度 方便恢复
    //QString picPath;
    bool isRecoverTask;// 记录是否继续上次的截图 还是重新截图[图片路径不一样]
    bool isTaskInfoError;
};

class TaskWorker :public QThread
{
    Q_OBJECT
public:
    explicit TaskWorker(QThread *parent = nullptr);

    ~TaskWorker();
    // 错误状态
    enum RESULT{DOING =0x01, DOWN = 0x02, FAILED = 0x03};

    // 线程状态 未运行 下载主题 截图 上传图片
    enum TASKSTATUS{DISRUN=0x01, DOWNTHEME=0x02, SCREENCAP=0x03, UPPICTURE=0x04};

    TaskInfo taskInfo;
    bool m_stop;
    void copyData(Phones *phone);
    void downLoadTheme();


private:
    QFile themeFile;
    QFile zipFile;
    QNetworkReply* reply;

    int sendtime;
    int finishtime;
    void startJiShi();
    void endJiShi();

    int threadStatus;
//    int resultCode;

    QNetworkAccessManager *workerHttp;// download theme and upload pic
    QNetworkAccessManager *uploadHttp;

    void initTaskListVersion();

    void delTempFiles();

public slots:

    void onDownThemeFinished(QNetworkReply* reply);
    void onUploadPicFinished(QNetworkReply * reply);
    void startWorkingSlot();
    void postTaskResults(int taskId, int status, const QByteArray &err_str);
    // 触发
    void run();
    //bool isRunning();
    void onErrorSlot(QNetworkReply::NetworkError error);

signals:
    void startWorkingSig();
    void postTaskResultsSig(int taskId, int status, const QByteArray & err_str);

};



#endif // TASKWORKER_H
