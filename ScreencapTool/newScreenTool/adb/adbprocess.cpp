#include "adbprocess.h"
//#include "assert.h"
#include <QApplication>
#include <QDebug>
#include "phones.h"


AdbProcess::AdbProcess()
{
    connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)));
    connect(this, &AdbProcess::errorOccurred, this, [this](QProcess::ProcessError error){
        if (QProcess::FailedToStart == error) {
            emit adbResultHandleSig(ADB_ERROR_OTHER);
        }

    });

    adbExe = QApplication::applicationDirPath();
    adbExe.append("/plugins/adb/adb.exe");

    initSignals();


}

AdbProcess::~AdbProcess()
{
    qDebug("adb kill");

}


void AdbProcess::initSignals()
{
    connect(this, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this,
          [this](int exitCode, QProcess::ExitStatus exitStatus){
        if (NormalExit == exitStatus && 0 == exitCode) {
            emit adbResultHandleSig(ADB_SUCESS_EXEC);
        } else {
            //P7C0218510000537        unauthorized ,手机端此时弹出调试认证，要允许调试
            emit adbResultHandleSig(ADB_ERROR_EXEC);
        }
//        qDebug() << "adb return " << exitCode << "exit status " << exitStatus;

        if (exitCode == 1) {
            system("adb kill-server");
        }
    });

    connect(this, &QProcess::errorOccurred, this,
            [this](QProcess::ProcessError error){
        if (QProcess::FailedToStart == error) {
            //emit adbResultHandleSig(AER_ERROR_MISSING_BINARY);
            //assert(QProcess::FailedToStart != error);
        } else {
            emit adbResultHandleSig(ADB_ERROR_EXEC);
            QString err = QString("qprocess start error:%1 %2").arg(program()).arg(arguments().join(" "));
            qCritical(err.toStdString().c_str());
        }
    });

    connect(this, &QProcess::readyReadStandardError, this,
            [this](){
        QString tmp = QString::fromLocal8Bit(readAllStandardError()).trimmed();
        m_error_str += tmp;
        qWarning(QString("AdbProcess::error:%1").arg(tmp).toUtf8());
    });

    connect(this, &QProcess::readyReadStandardOutput, this,
            [this](){
        QString tmp = QString::fromLocal8Bit(readAllStandardOutput()).trimmed();
        m_stdout_str += tmp;
//        qDebug(QString("AdbProcess::out:%1").arg(tmp).toUtf8());
    });

    connect(this, &QProcess::started, this,
            [this](){
        //emit adbResultHandleSig(AER_SUCCESS_START);
        //qDebug() << "adb start";
    });
}


void  AdbProcess::execAdbCommod(const QString& serial, const QString& commd)
{

    m_stdout_str = "";
    m_error_str = "";
    QString tempCommd;//("C:\\Windows\\System32\\cmd.exe ");
    tempCommd.append(adbExe);
    if (!serial.isEmpty()) {
        tempCommd.append(" -s ");
        tempCommd.append(serial);
    }
    bool status = true;
    // add 9.20
    if(state() == QProcess::Running && !waitForFinished(3000)){
        status = false;
        this->kill();
    }

    if(status){
        tempCommd.append(" ");
        tempCommd.append(commd);

        start(tempCommd);
    }
}


// 结果处理
void AdbProcess::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (NormalExit == exitStatus && 0 == exitCode) {
        emit adbResultHandleSig(ADB_SUCESS_EXEC);// 成功执行
    } else {
        emit adbResultHandleSig(ADB_ERROR_EXEC);//本地连接
    }
}




QStringList AdbProcess::getDevicesSerialFromStdOut()
{
    // get devices serial by adb devices
    QStringList serials;
    QStringList devicesInfoList = m_stdout_str.split(QRegExp("\r\n|\n"), QString::SkipEmptyParts);
    for (QString deviceInfo : devicesInfoList) {
        QStringList deviceInfos = deviceInfo.split(QRegExp("\t"), QString::SkipEmptyParts);
        if (2 == deviceInfos.count() && 0 == deviceInfos[1].compare("device")) {
            serials << deviceInfos[0];
        }
    }

    return serials;
}

QString AdbProcess::getStdOut()
{
    return m_stdout_str;
}

QString AdbProcess::getErrorOut()
{
    return m_error_str;
}
