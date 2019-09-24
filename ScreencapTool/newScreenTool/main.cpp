#include <QApplication>
#include "widget.h"
#include <QTextCodec>
#include <QMutex>
#include <QFileInfo>
#include <QDir>

// 实现功能：重定向qDebug，让输出全部输到文件内，在log内进行函数实现
void qMyLog(QtMsgType type, const QMessageLogContext &context, const QString &msg);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 设置编码
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    qInstallMessageHandler(qMyLog);// 回调函数 通过句柄注册 qInfo不会输出到文件

    QString program = QCoreApplication::applicationDirPath();
    QStringList parLit;
    QProcess* p = new QProcess();
    program.append("/del.bat");
    QFileInfo fileinfo(program);
    qDebug() << fileinfo.filePath() << parLit;
    p->start(fileinfo.absoluteFilePath(), parLit);


    Widget w;
    w.show();

    return a.exec();
}



void qMyLog(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    static QMutex mutex;
    mutex.lock();

    QString msgStr;
    switch (type) {
    case QtDebugMsg:
        msgStr.append("Debug:").append(msg);
        break;
    case QtWarningMsg:
        msgStr.append("Warning:").append(msg);
        break;
    case QtCriticalMsg:
        msgStr.append("Critical:").append(msg);
        break;
    case QtFatalMsg:
        msgStr.append("Fatal:").append(msg);
        break;
    default:
        break;
    }

    // 输出到文件：log2019-08-09.txt unix类型文件
    QString s = QTime::currentTime().toString(Qt::ISODate).append(": ").append(msgStr);
//    s.append(context.file);
    QString logNameStr = QString("log").append(QDate::currentDate().toString(Qt::ISODate)).append(".txt");

    QFile file(logNameStr);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream textStream(&file);
        textStream.setCodec("UTF-8");//设置输出编码
        textStream << s;
        endl(textStream);
        file.flush();
        file.close();
    }

    mutex.unlock();
}
