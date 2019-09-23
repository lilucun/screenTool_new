#include "xmlreader.h"
#include <QFile>
#include <QDebug>

XmlReader::XmlReader(QObject *parent) : QObject(parent)
{

}

PhoneCharacters XmlReader::getPhoneCharater(const QString &serial)
{

}


bool XmlReader::readQIODevice(QIODevice *device)
{
    reader.setDevice(device);
    // 找到第一个有效标记
    if(reader.readNextStartElement()){
        QString root = reader.name().toString();
        if(root == "Phones"){
            QXmlStreamAttributes attributes = reader.attributes();// 获取root所有属性
            if(attributes.hasAttribute("version")){
                QString version = attributes.value("version").toString();
                if(version == "1.0"){
                    qDebug() << "root:" << root << " version:" << version;
                    readRootMark();// 读取root元素的内容
                } else {

                }
            } else {

            }
        } else {
            qCritical() << "xmlRead root error: " << reader.errorString();
        }
    } else {
        qCritical() << "XmlRead error:" << reader.errorString() << reader.lineNumber();
    }

    return true;
}

bool XmlReader::readXml(const QString &xmlFileName)
{
    QFile file(xmlFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qCritical() << "文件打开失败";
        return false;
    }

//    readQIODevice(&file);
    reader.setDevice(&file);
//        qCritical() << "read xml failed..";
//        file.close();
//        return false;
//    }



    if(!tempList.isEmpty())
        tempList.clear();
    // 找到第一个有效标记
    if(reader.readNextStartElement()){
        QString root = reader.name().toString();
        if(root == "Phones"){
            QXmlStreamAttributes attributes = reader.attributes();// 获取root所有属性
            if(attributes.hasAttribute("version")){
                QString version = attributes.value("version").toString();
                if(version == "1.0"){
                    qDebug() << "root:" << root << " version:" << version;
                    while(reader.readNextStartElement()){
                        if(reader.name().toString() == "Phone"){
                            PhoneCharacters charater;

                            while(reader.readNextStartElement()){
                                if(reader.name().toString() == QString::fromUtf8("序列号")){
                                    QString serial = reader.readElementText();
                                    qDebug() << "serial:" << serial;
                                    charater.phoneSerial = serial;
                                } else if(reader.name().toString() == QString::fromUtf8("系统版本")){
                                    QString version = reader.readElementText();
                                    qDebug() << "version:" << version;
                                    charater.phoneVersion = version;
                                } else if(reader.name().toString() == QString::fromUtf8("制造商")){
                                    QString menufest = reader.readElementText();
                                    qDebug() << "menufest:" << menufest;
                                    charater.phoneMenufest = menufest;
                                } else if(reader.name().toString() == QString::fromUtf8("型号")){
                                    QString product = reader.readElementText();
                                    qDebug() << "product:" << product;
                                    charater.phoneProduct = product;
                                } else if(reader.name().toString() == QString::fromUtf8("屏幕大小")){
                                    QString size = reader.readElementText();
                                    qDebug() << "size:" << size;

                                    size = size.simplified();// 空格
                                    int i = size.indexOf("x");
                                    charater.wm_size.width = size.left(i).toInt();
                                    charater.wm_size.height = size.right(size.size() - i - 1).toInt();
                                } else {
                                    reader.skipCurrentElement();
                                }
                            }

                            tempList.insert(charater.phoneSerial, charater);

                        } else {
                            reader.skipCurrentElement();// 跳过当前元素
                        }
                    }
                }


            }
        } else {
            qCritical() << "xmlRead root error: " << reader.errorString();
        }
    } else {
        qCritical() << "XmlRead error:" << reader.errorString() << reader.lineNumber();
    }

    file.close();
    return true;
}

QMap<QString, PhoneCharacters> XmlReader::getList()
{
    return tempList;
}

void XmlReader::readRootMark()
{
    // 循环定位到开始标记
    while(reader.readNextStartElement()){
        if(reader.name().toString() == "Phone"){
            readFirstChirldsMark();
        } else {
            reader.skipCurrentElement();// 跳过当前元素
        }
    }
}

void XmlReader::readFirstChirldsMark()
{
//    Q_ASSERT(reader.isStartElement() && reader.name().toString() == "HuaWei8");

    while(reader.readNextStartElement()){
        if(reader.name().toString() == QString::fromUtf8("序列号")){
            readSerialMark();
        } else if(reader.name().toString() == QString::fromUtf8("系统版本")){
            readVersionMark();
        } else if(reader.name().toString() == QString::fromUtf8("制造商")){
            readMenufestMark();
        } else if(reader.name().toString() == QString::fromUtf8("型号")){
            readProductMark();
        } else if(reader.name().toString() == QString::fromUtf8("屏幕大小")){
            readPhoneSizeMark();
        } else {
            reader.skipCurrentElement();
        }
    }
}

void XmlReader::readSerialMark()
{
    QString serial = reader.readElementText();
    qDebug() << "serial:" << serial;
//    charater.phoneSerial = serial;
}

void XmlReader::readProductMark()
{
    QString product = reader.readElementText();
    qDebug() << "product:" << product;
//    charater.phoneProduct = product;
}

void XmlReader::readMenufestMark()
{
    QString menufest = reader.readElementText();
    qDebug() << "menufest:" << menufest;
//    charater.phoneMenufest = menufest;
}

void XmlReader::readVersionMark()
{
    QString version = reader.readElementText();
    qDebug() << "version:" << version;
//    charater.phoneVersion = version;
}

void XmlReader::readPhoneSizeMark()
{
    QString size = reader.readElementText();
    qDebug() << "size:" << size;

    size = size.simplified();// 空格
    int i = size.indexOf("x");
//    charater.wm_size.height = size.left(i).toInt();
//    charater.wm_size.width = size.right(size.size() - i - 1).toInt();
}
