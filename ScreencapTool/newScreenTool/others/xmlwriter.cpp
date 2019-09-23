#include "xmlwriter.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QDebug>

XmlWriter::XmlWriter(QObject *parent) : QObject(parent)
{
    xmlUi = new XmlConfigUi;
    connect(xmlUi, SIGNAL(writeXmlSignal()), this, SLOT(writeXmlSlot()));
}

void XmlWriter::writeXml(const QString &xmlFileName)
{
    QFile file(xmlFileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qCritical() << "文件打开失败";
        return;
    }

    QXmlStreamWriter writer(&file);
    // 自动格式化
    writer.setAutoFormatting(true);
    /************  写头部：声明 注释 处理指令 ***********/
    writer.writeStartDocument("1.0", true); // 声明 1.0 utf-8
    writer.writeComment(QString::fromUtf8("你好，世界！"));// 注释
//    writer.writeProcessingInstruction("xml-stylesheet type=\"text/css\" href=\"style.css\"");//解析指令？

    // 写CDATA数据
    //    writer.writeCDATA(QString::fromLocal8Bit("我是你爸爸！"));

    /************** 写头标记 *******/
    writer.writeStartElement("Phones");
    writer.writeAttribute("version", "1.0");//属性

    writer.writeStartElement("HuaWei8");
    writer.writeTextElement(QString::fromUtf8("序列号"), xmlUi->getSerial());
    writer.writeTextElement(QString::fromUtf8("系统版本"), xmlUi->getVersion());
    writer.writeTextElement(QString::fromUtf8("制造商"), xmlUi->getProduct());
    writer.writeTextElement(QString::fromUtf8("型号"), xmlUi->getModel());
    writer.writeTextElement(QString::fromUtf8("屏幕大小"), xmlUi->getSize());

    writer.writeEndElement();// 结束 HuaWei8 标记

    writer.writeEndElement();// 结束 Phones 标记
    writer.writeEndDocument();// 结束文档

    file.close();
}

void XmlWriter::show()
{
    xmlUi->show();
}

void XmlWriter::writeXmlSlot()
{
    writeXml("phones.xml");
    qDebug() << "write";
    xmlUi->hide();
}
