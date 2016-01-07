#include "photogram.h"

Photogram::Photogram(QByteArray &data, float angleOfRotation):
    angle{angleOfRotation}, sinAngle{sineAngle(angle)}, cosAngle{cosineAngle(angle)}
{
    createImages(data);
    computeVertices(cvImage);
}
Photogram::Photogram(const Photogram &p):
    vertices{p.vertices}, qtImage{p.qtImage}, cvImage{p.cvImage},
    threshold{p.threshold}, angle{p.angle}, sinAngle{p.sinAngle}, cosAngle{p.cosAngle}
{}
Photogram::Photogram()
{}

QImage& Photogram::getImage()
{
    return qtImage;
}
std::vector<QVector3D>& Photogram::getVertices()
{
    return vertices;
}
void Photogram::createImages(QByteArray &data)
{
    qtImage = QImage::fromData(data, "JPG");
//    qtImage.save("qtImage.jpg","JPG");

    cv::Mat tmp(qtImage.height(),qtImage.width(), CV_8UC4,(uchar*)qtImage.bits(),qtImage.bytesPerLine());
    cv::cvtColor(tmp, cvImage, cv::COLOR_BGR2GRAY);
//    cv::imwrite( "cvImage2.jpg", cvImage);
}
void Photogram::computeVertices(cv::Mat &image)
{
    int imageWidth  = image.cols;
    int imageHalfHeight = image.rows / 2;

    for(int y = 0; y < imageHalfHeight; y++)
    {
        int positionBrightestPixel = -1;
        int valueBrightestPixel = threshold;

        for(int x = 1280; x < imageWidth; x++)
        {
            uchar brightness{image.at<uchar>(y,x)};

            if(brightness > valueBrightestPixel)
            {
                valueBrightestPixel = brightness;
                positionBrightestPixel = x;
            }
        }
        if(valueBrightestPixel > threshold)
            mathTransformation(positionBrightestPixel,y);
    }
}
void Photogram::mathTransformation(int x, int y)
{
    float e = (float)(x - 1280)/128;
    float f = (float)(960 - y)/2560;

    QLineF gLine(0, 0, 20, 11.5);
    QLineF nLine(20, 0, 0, e);
    QPointF xPos{};                 //--punkt przecięcia
    nLine.intersect(gLine, &xPos);  //--nadanie mu wartości

    QLineF n(20, 0, xPos.x(), xPos.y());     //--linia od kamery do punktu przecięcia (do linii)
    float r   = 2.0 * xPos.y();     //--na podstawie trójkąta 30, 60, 90
    float yCm = f * (n.length());   //--

    float xp = r * cosAngle;
    float yp = r * sinAngle;
    float zp = yCm;

    return vertices.push_back(QVector3D(xp, zp, yp));
}

float Photogram::sineAngle(float angle)
{
    return qSin(qDegreesToRadians(angle));
}
float Photogram::cosineAngle(float angle)
{
    return qCos(qDegreesToRadians(angle));
}
