#ifndef XMLCONFIGUI_H
#define XMLCONFIGUI_H

#include <QWidget>
#include "ui_xmlconfigui.h"

namespace Ui {
class XmlConfigUi;
}

class XmlConfigUi : public QWidget
{
    Q_OBJECT

public:
    explicit XmlConfigUi(QWidget *parent = 0);
    ~XmlConfigUi();

    QString getSerial();
    QString getVersion();
    QString getSize();
    QString getProduct();
    QString getModel();

signals:
    void writeXmlSignal();

private slots:
    void on_ok_btn_clicked();

private:
    Ui::XmlConfigUi *ui;
};

#endif // XMLCONFIGUI_H
