#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include <QObject>
#include <QXmlStreamReader>
#include "xmlconfigui.h"

class XmlManager : public QObject
{
    Q_OBJECT
public:
    explicit XmlManager(QObject *parent = nullptr);

    XmlManager(const QString &xmlName);
    void setXmlFileName(const QString &xmlFileName);

    void writeXml(const QString &xmlFileName);

    /***************** 读xml **********************/
    bool readQIODevice(QIODevice *device);
    void readXml(const QString &xmlFileName);
    void readRootMark();
    void readFirstChirldsMark();
    void readSerialMark();
    void readProductMark();
    void readMenufestMark();
    void readVersionMark();
    void readPhoneSizeMark();
private:
    QXmlStreamReader reader;
    XmlConfigUi *ui;

signals:

public slots:
};

#endif // XMLMANAGER_H
