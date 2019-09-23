#ifndef QUAZIPINTERFACE_H
#define QUAZIPINTERFACE_H

#include <QObject>
#include <QString>
#include <QIODevice>
class QuazipInterface
{
public:
    virtual ~QuazipInterface() {}

    virtual void extractZip(QString src, QString des) = 0;
    virtual void compressZip(QString des, QString src) = 0;
};

#define QuazipInterface_IID "org.qt-project.quazipinterface"
Q_DECLARE_INTERFACE(QuazipInterface, QuazipInterface_IID)
#endif // QUAZIPINTERFACE_H
