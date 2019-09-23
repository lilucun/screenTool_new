#include "xmlconfigui.h"
#include <QDebug>

XmlConfigUi::XmlConfigUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XmlConfigUi)
{
    ui->setupUi(this);

}

XmlConfigUi::~XmlConfigUi()
{
    delete ui;
}

QString XmlConfigUi::getSerial()
{
    return ui->edit_serial->text();
}

QString XmlConfigUi::getVersion()
{
    return ui->edit_version->text();
}

QString XmlConfigUi::getSize()
{
    return ui->edit_phoneSize->text();
}

QString XmlConfigUi::getProduct()
{
    return ui->edit_product->text();
}

QString XmlConfigUi::getModel()
{
    return ui->edit_model->text();
}

void XmlConfigUi::on_ok_btn_clicked()
{
    emit writeXmlSignal();
    qDebug() << "kdkdkd";
}
