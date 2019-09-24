#include "taskworker.h"
#include <QDebug>
#include <QNetworkReply>
#include <QFileInfo>
#include <sys/time.h>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QJsonParseError>
#include <QPluginLoader>
#include <quazipInterface.h>
#include <QDir>
#include "huaweiphones.h"

#define release_test

TaskWorker::TaskWorker(QThread *parent)
{
    Q_UNUSED(parent);
//    threadStatus = TaskWorker::DISRUN;
//    resultCode = TaskWorker::FAILED;

    workerHttp = new QNetworkAccessManager(this);
    uploadHttp = new QNetworkAccessManager(this);
    connect(workerHttp, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDownThemeFinished(QNetworkReply*)));
    connect(uploadHttp, SIGNAL(finished(QNetworkReply*)), this, SLOT(onUploadPicFinished(QNetworkReply*)));

    connect(this, SIGNAL(startWorkingSig()), this, SLOT(startWorkingSlot()));
    connect(this, SIGNAL(postTaskResultsSig(int, int, const QByteArray &)), this, SLOT(postTaskResults(int, int, const QByteArray&)));

    m_stop = false;

}

TaskWorker::~TaskWorker()
{
    qDebug("delete worker");

    delTempFiles();
}

void TaskWorker::startJiShi()
{
    struct timeval tvsend;
    gettimeofday(&tvsend,NULL);    //????????sys/time.h??????
    sendtime = tvsend.tv_sec * 1000 + tvsend.tv_usec / 1000;
}

void TaskWorker::endJiShi()
{

    struct timeval tvfish;
    gettimeofday(&tvfish,NULL);    //头文件sys/time.h
    finishtime = tvfish.tv_sec * 1000 + tvfish.tv_usec / 1000;
    qWarning() << "============== time:" << finishtime - sendtime;

}



void TaskWorker::downLoadTheme()
{
    // 线程状态
//    threadStatus = TaskWorker::DOWNTHEME;

    startJiShi();

    if (taskInfo.themeUrl.isEmpty()) {
        qCritical("themeUrl is null");
        this->postTaskResults(taskInfo.taskId, TaskWorker::FAILED, "task theme url is nill");
        return;
    }

    taskInfo.themeName.clear();
    taskInfo.themeName.append(QString("./temp/%1.hwt").arg(taskInfo.taskId));

    if(QFile::exists(taskInfo.themeName))
        QFile::remove(taskInfo.themeName);
    // 修改文件名
    themeFile.setFileName(taskInfo.themeName);

    QNetworkRequest request;
    request.setUrl(QUrl(taskInfo.themeUrl));
    workerHttp->get(request);
}

// 数据的拷贝
void TaskWorker::copyData(Phones *phone)
{
    if(phone == NULL)
        return;

    this->taskInfo.menufest = phone->getPhoneMenufest();
    this->taskInfo.phoneVersion = phone->getPhoneVersion();// ?????
    this->taskInfo.product = phone->getPhoneProduct();
    this->taskInfo.serial = phone->getPhoneSerial();

    this->taskInfo.phone = phone;

    initTaskListVersion();
}
// 任务版本初始化
void TaskWorker::initTaskListVersion()
{

    if (this->taskInfo.phoneVersion.isEmpty()) {
        this->taskInfo.taskListVersion = GetPhoneObject::HuaWei8;
        return;
    }
    bool ok;

    int num = taskInfo.phoneVersion.left(1).toInt(&ok);
    if (ok) {
        if (num == 8) {
            taskInfo.taskListVersion = GetPhoneObject::HuaWei8;
        } else if(num == 9) {
            taskInfo.taskListVersion = GetPhoneObject::HuaWei9;
        } else {
        }
    }
}

void TaskWorker::delTempFiles()
{

    if(themeFile.isOpen())
        themeFile.close();

    if(zipFile.isOpen())
        zipFile.close();

//    QString path(taskInfo.phone->getPicturePath());
//    if(!path.isEmpty() || path.size() < 2) {
//        path = path.left(path.size() - 1);// 返回整个字符串，当size 小于1时

//        QDir dir(path);
//        if (dir.exists()) {
//            qDebug() << "delete dir:" << path;
//            dir.removeRecursively();
//        }
//    }

    if (zipFile.exists()) {
        qDebug() << "delete zipFie:" << QFileInfo(zipFile).absoluteFilePath();
        zipFile.remove();
    }
    if(themeFile.exists()) {
        qDebug() << "delete themeFile:" << QFileInfo(themeFile).absoluteFilePath();
        themeFile.remove();
    }


}


// 任务回传结果
// TaskWorker::DOWN 任务成功 回传zip图片
// TaskWorker::FAILED 任务失败
void TaskWorker::postTaskResults(int taskId, int status, const QByteArray &err_str)
{
    // 更新状态
    if(taskInfo.phone->getPhoneStatues() == Phones::devBusy
            || taskInfo.phone->getPhoneStatues() == Phones::devAcceptTask) {
        taskInfo.phone->setPhoneStatues(Phones::devReady);
    }

    switch (status) {
    case TaskWorker::DOWN:
    {
        // 压缩
        QString temp(taskInfo.phone->getPicturePath());
        if (!temp.isEmpty()) {
            temp = temp.left(temp.size() - 1);
            int index = temp.lastIndexOf("/");
            temp = temp.right(temp.size() - index - 1);
        }

        QuazipInterface *face;
        QPluginLoader loader("QuazipPlugin.dll");
        QObject  *object = loader.instance();
        qCritical() << "plugin error:" <<loader.errorString();

        if (object != NULL) {
            face = qobject_cast<QuazipInterface*> (object);
            if (face) {
#ifndef release_test
                face->compressZip(QString("./release/temp/%1.zip").arg(temp), QString("./release/temp/%1").arg(temp));
#else
                face->compressZip(QString("./temp/%1.zip").arg(temp), QString("./temp/%1").arg(temp));
#endif
            }
        }
        delete object;

        QString url("http://");
        url.append(IP_ADDR);
        url.append(":");
        url.append(QString("%1").arg(HTTP_PORT));
        url.append("/tool/task/result?taskId=");
        url.append(QString::number(taskId));
        url.append("&status=");
        url.append(QString::number(status));
        qDebug() << url;

        // ??????
        QHttpMultiPart *multi = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart zipPart;
#ifndef release_test
        zipFile.setFileName(QString("./release/temp/%1.zip").arg(temp));
#else
        zipFile.setFileName(QString("./temp/%1.zip").arg(temp));
#endif
        if (!zipFile.open(QIODevice::ReadOnly)) {
            //assert(1 == 0);
            qCritical("upload zip is not exit");
            return;
        }

        zipPart.setBodyDevice(&zipFile);
        zipPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/zip"));
        QString str;
        str.append(QString("form-data;name=\"themeFile\";filename=\"%1.zip\"").arg(temp));
        zipPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(str));
        multi->append(zipPart);

        QNetworkRequest res;
        res.setUrl(QUrl(url));
        QNetworkReply* re = uploadHttp->post(res,  multi);

        connect(re, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
                [=](QNetworkReply::NetworkError code){
            qCritical() << "err:" << code;

            zipFile.close();
            re->deleteLater();
        });
    }
        break;

    case TaskWorker::FAILED:
    {

        QString url("http://");
        url.append(IP_ADDR);
        url.append(":");
        url.append(QString("%1").arg(HTTP_PORT));
        url.append("/tool/task/result?taskId=");
        url.append(QString::number(taskId));
        url.append("&status=");
        url.append(QString::number(7));// status
        url.append("&statusMsg=");
        url.append(err_str);
        qDebug() << url;

        QNetworkRequest res;
        res.setUrl(QUrl(url));
        res.setRawHeader("Content-Type", "application/json");
        uploadHttp->post(res, QByteArray(""));
        // 终止线程
        if(this->isRunning()){
            this->terminate();
            this->wait();
        }
    }
        break;
    default:
        break;
    }

}

// 下载主题
void TaskWorker::onDownThemeFinished(QNetworkReply *reply)
{
    RESULT resultCode = TaskWorker::FAILED;

    do{
        // 小于1M
        if (reply->bytesAvailable() <= 0) {
//            resultCode = TaskWorker::FAILED;
            qCritical() << "theme is less 1M";
        } else {
            if (!themeFile.open(QIODevice::WriteOnly)) {
                qCritical() << "file open failed";
//                resultCode = TaskWorker::FAILED;
                break;
            }

            themeFile.write(reply->readAll());

            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "the theme download no error";
                emit startWorkingSig();
                resultCode = TaskWorker::DOWN;
            } else {
                qCritical() <<"the theme download error:" << reply->errorString();
//                resultCode = TaskWorker::FAILED;
            }
        }
    }while(0);


    if(resultCode == TaskWorker::FAILED)
        this->postTaskResults(taskInfo.taskId, TaskWorker::FAILED, "download theme failed");

    if(themeFile.isOpen())
        themeFile.close();

    reply->deleteLater();
}
// 返回结果响应
void TaskWorker::onUploadPicFinished(QNetworkReply *reply)
{
    QByteArray arr = reply->readAll();
    qDebug() << "taskworker http arr:" << arr;

    QJsonParseError json_error;
    //QJsonDocument::fromBinaryData() 是不对的
    QJsonDocument jsonDoc(QJsonDocument::fromJson(arr, &json_error));
    if (json_error.error != QJsonParseError::NoError)
        qCritical() << "json error!";

    QJsonObject obj2 = jsonDoc.object();
    int ret = obj2.value("code").toInt();
    if (ret == 1) {
        qDebug("upload picture sucess!");
    } else {
        qCritical("upload picture failed....");
    }

    if (zipFile.isOpen())
        zipFile.close();

    endJiShi();

    reply->deleteLater();

//    delTempFiles();
}

// 工作
void TaskWorker::startWorkingSlot()
{
    this->start();
}

// run函数
void TaskWorker::run()
{
    qCritical() << "taskList size:" << taskInfo.appList.size();
    if(taskInfo.menufest.contains("huawei", Qt::CaseInsensitive)){
        HuaWeiPhones *phone = nullptr;
        phone = dynamic_cast<HuaWeiPhones*>(this->taskInfo.phone);
        if(phone){
            phone->pushThemeToPhone(this->taskInfo.themeName);
            phone->initPicPath();
            phone->themeInstall();

            for (int i = 0; i < taskInfo.appList.size(); ++i) {
                qDebug() << taskInfo.appList[i];
                this->taskInfo.taskProcessId = taskInfo.appList[i];
                if (!m_stop) {
                    phone->taskIdSwitch(taskInfo.appList[i]);
                } else {
                    break;
                }
            }
            emit this->postTaskResultsSig(taskInfo.taskId, TaskWorker::DOWN, "");
        }else{
            emit this->postTaskResultsSig(taskInfo.taskId, TaskWorker::FAILED, "phone is null");
        }

    }
}

void TaskWorker::onErrorSlot(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
    qCritical() << "http error ";

}
