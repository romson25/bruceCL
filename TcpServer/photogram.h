#ifndef PHOTOGRAM_H
#define PHOTOGRAM_H

#include <QDebug>
#include <QImage>
#include <QtMath>
#include <vector>
#include <QVector>
#include <QVector3D>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class Photogram
{
public:
    Photogram();
    Photogram(const Photogram &p);
    Photogram(QByteArray &data, float angleOfRotation);

    QImage &getImage();
    std::vector<QVector3D> &getVertices();

private:
    void createImages   (QByteArray &data);

    void computeVertices    (cv::Mat&);
    void mathTransformation (int x, int y);

    float sineAngle     (float angle);
    float cosineAngle   (float angle);

    std::vector<QVector3D> vertices {};
    QImage  qtImage {};
    cv::Mat cvImage {};

    float threshold {};
    float angle     {};
    float sinAngle  {};
    float cosAngle  {};
};

#endif // PHOTOGRAM_H
