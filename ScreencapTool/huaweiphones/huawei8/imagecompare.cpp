#include "imagecompare.h"
#include <QTextCodec>
#include <QDebug>


ImageCompare::ImageCompare(){
//    log = new MyLog;
}



int ImageCompare::compareImageResults(const QString &baseImage, const QString &image, int pox_x, int pox_y, int w, int h)
{

    Mat cvmBaseImage, cvmImage;                           // 创建图片类
    int iResult = -1;                                          // 定义返回结果

//    QTextCodec *codec = QTextCodec::codecForName("utf-8");  // 将编码转换成GBK编码，读图片操作为读取GBK编码
//    QTextCodec::setCodecForLocale(codec);

    cvmBaseImage = imread(baseImage.toLocal8Bit().toStdString(),1); // 读图片
    cvmImage = imread(image.toLocal8Bit().toStdString(),1);

//    qDebug() << "read pic:" << iResult;

    if (!cvmBaseImage.data) {                                         // 判断是否加载成功
        qDebug() << "read cvmBaseImage error";
        return -1;
    }

    if (!cvmImage.data)
    {
        qDebug() << "read cvmImage error";
        return -1;
    }

    Rect rect(pox_x, pox_y, w, h);                                 // 截取ROI区域
    Mat cvmBaseImageRect = cvmBaseImage(rect);
    Mat cvmImage_Rect = cvmImage(rect);

    Mat cvmSubImage = cvmBaseImageRect - cvmImage_Rect;            // 图像做差

    Mat cvmGrayImage;                                              // 图像转灰
    cvtColor(cvmSubImage, cvmGrayImage, CV_BGR2GRAY);

    Mat cvmBinImage;                                               // 二值化操作
    threshold(cvmGrayImage, cvmBinImage,0,255, THRESH_BINARY);


    int iNum = 0;                                                      // 遍历像素，获取白色像素值个数
    for (int i = 0; i < cvmBinImage.rows; i++) {
        for (int j = 0; j < cvmBinImage.cols; j++) {
            int ipiex = cvmBinImage.at<uchar>(i, j);

            if (ipiex == 255) {
                iNum++;
            } else {
                iNum = iNum + 0;
            }

        }
    }

    // 这边的4可以改的
    if (iNum > 100){                                        // 如果做差之后，图片不一样，则就存在物体，物体的像素值会占据很大的个数
        iResult = 1;                                               // 1代表图片是不一样的
    } else {
        iResult = 0;
    }

    return iResult;
}
