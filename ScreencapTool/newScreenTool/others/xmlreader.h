#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include <QXmlStreamReader>
#include "phones.h"
#include <QMap>

class XmlReader : public QObject
{
    Q_OBJECT
public:
    explicit XmlReader(QObject *parent = nullptr);

    PhoneCharacters getPhoneCharater(const QString &serial);

    /***************** 读xml **********************/
    bool readQIODevice(QIODevice *device);
    bool readXml(const QString &xmlFileName);

    QMap<QString, PhoneCharacters> getList();
    void readRootMark();
    void readFirstChirldsMark();
    void readSerialMark();
    void readProductMark();
    void readMenufestMark();
    void readVersionMark();
    void readPhoneSizeMark();


private:
    QXmlStreamReader reader;
    QMap<QString, PhoneCharacters> tempList;
signals:

public slots:
};

#endif // XMLREADER_H
