#include "xmlmanager.h"
#include <QFile>
#include <QDebug>

XmlManager::XmlManager(QObject *parent) : QObject(parent)
{
    ui = new XmlConfigUi;
}

void XmlManager::setXmlFileName(const QString &xmlFileName)
{

}

void XmlManager::writeXml(const QString &xmlFileName)
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
    writer.writeComment(QString::fromLocal8Bit("你好，世界！"));// 注释
//    writer.writeProcessingInstruction("xml-stylesheet type=\"text/css\" href=\"style.css\"");//解析指令？

    // 写CDATA数据
    //    writer.writeCDATA(QString::fromLocal8Bit("我是你爸爸！"));

    /************** 写头标记 *******/
    writer.writeStartElement("Phones");
    writer.writeAttribute("version", "1.0");//属性

    writer.writeStartElement("HuaWei8");
    writer.writeTextElement(QString::fromLocal8Bit("序列号"), "");
    writer.writeTextElement(QString::fromLocal8Bit("系统版本"), "8.0.1");
    writer.writeTextElement(QString::fromLocal8Bit("制造商"), "HuaWei");
    writer.writeTextElement(QString::fromLocal8Bit("型号"), "BLK_AL00");
    writer.writeTextElement(QString::fromLocal8Bit("屏幕大小"), "1080x1920");

    writer.writeEndElement();// 结束 HuaWei8 标记

    writer.writeEndElement();// 结束 Phones 标记
    writer.writeEndDocument();// 结束文档

    file.close();
}

bool XmlManager::readQIODevice(QIODevice *device)
{

}

void XmlManager::readXml(const QString &xmlFileName)
{

}

void XmlManager::readRootMark()
{

}

void XmlManager::readFirstChirldsMark()
{

}

void XmlManager::readSerialMark()
{

}

void XmlManager::readProductMark()
{

}

void XmlManager::readMenufestMark()
{

}

void XmlManager::readVersionMark()
{

}

void XmlManager::readPhoneSizeMark()
{

}
