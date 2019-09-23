#ifndef ADBDEVICES_H
#define ADBDEVICES_H

#include <QString>

class AdbDevices
{
public:
    AdbDevices();

    QStringList getDevicesSerials();

    bool adbDevices();
private:
    QString m_out;
    QString adbExe;
};

#endif // ADBDEVICES_H
