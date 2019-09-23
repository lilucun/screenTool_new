#ifndef ADBPROCESS_H
#define ADBPROCESS_H

#include <QProcess>
#include <QObject>


// adb 执行
class AdbProcess:public QProcess
{
    Q_OBJECT
public:
    enum ADB_STATUS{
      ADB_SUCCESS_START,// 启动成功
       ADB_ERROR_START,// 启动失败
        ADB_SUCESS_EXEC,// 执行成功
        ADB_ERROR_EXEC,// 执行失败
        ADB_ERROR_OTHER // 其他错误
    };


    AdbProcess();
    ~AdbProcess();
    QString m_error_str;
    QString m_stdout_str;
    QString adbExe;

    QString getStdOut();
    QString getErrorOut();


    void execAdbCommod(const QString& serial, const QString& commd);

    QStringList getDevicesSerialFromStdOut();
    void initSignals();

public slots:
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

    //void adbResultHandleSlot(AdbProcess::ADB_STATUS status);
signals:
    void adbResultHandleSig(AdbProcess::ADB_STATUS status);

private:
    bool st = true;
};

#endif // ADBPROCESS_H
