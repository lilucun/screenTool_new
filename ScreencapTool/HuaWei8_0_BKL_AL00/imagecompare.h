#ifndef IMAGECOMPARE_H
#define IMAGECOMPARE_H

#include<QString>
#include <QObject>
#include "opencv2/opencv.hpp"

using namespace cv;

class ImageCompare
{

public:
    ImageCompare();

    int compareImageResults(const QString &baseImage, const QString &image, int pox_x, int pox_y, int w, int h);

};


#endif // IMAGECOMPARE_H
