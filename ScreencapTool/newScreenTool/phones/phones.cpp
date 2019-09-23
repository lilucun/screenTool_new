#include "phones.h"


Phones::Phones(QObject *parent) : QObject(parent)
{

}

Phones::Phones(const PhoneCharacters &characters)
{
    phoneStatues = Phones::devConn;
    this->phoneCharacters = characters;
    initPhone();
}

void Phones::initPhone()
{
    initPhoneAliveTime();
    phoneStatues = Phones::devReady;
}



int Phones::getPhoneStatues()
{
    return (int)this->phoneStatues;
}

void Phones::setPhoneStatues(int status)
{
    this->phoneStatues = status;
}

const QString Phones::getPhoneSerial()
{
    return this->phoneCharacters.phoneSerial;
}

void Phones::setPhoneSerial(const QString &id)
{
    this->phoneCharacters.phoneSerial = id;
}

const QString Phones::getPhoneMenufest()
{
    return this->phoneCharacters.phoneMenufest;
}

const QString Phones::getPhoneProduct()
{
    return this->phoneCharacters.phoneProduct;
}

void Phones::setPhoneProduct(const QString &product)
{
    this->phoneCharacters.phoneProduct = product;
}

const QString Phones::getPhoneVersion()
{
    return this->phoneCharacters.phoneVersion;
}

void Phones::setPhoneVersion(const QString &version)
{
    this->phoneCharacters.phoneVersion = version;
}

const ScreenSizeT Phones::getPhoneSize()
{
    return this->phoneCharacters.wm_size;
}

void Phones::setPhoneSize(const ScreenSizeT &size)
{
    this->phoneCharacters.wm_size.height = size.height;
    this->phoneCharacters.wm_size.width = size.width;
}


void Phones::initPhoneAliveTime()
{
    phoneAliveTime = 60 / UPDATE_TIME;
}

int Phones::getPhoneAliveTime()
{
    return phoneAliveTime;
}

void Phones::phoneAliveTimePlusOne()
{
    phoneAliveTime--;
}




