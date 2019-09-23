#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QObject>
#include "xmlconfigui.h"

class XmlWriter : public QObject
{
    Q_OBJECT
public:
    explicit XmlWriter(QObject *parent = nullptr);

    void writeXml(const QString &xmlFileName);
    void show();

private:
    XmlConfigUi *xmlUi;
signals:

public slots:
    void writeXmlSlot();

};

#endif // XMLWRITER_H
