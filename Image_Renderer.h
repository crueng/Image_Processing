#pragma once
#include <QPixmap>

class Image_Renderer
{
public:
	static void setBlackWhiteFilter(QImage& img);
	static void setVignetteFilter(QImage& img);
private:
	static const int getDistance(QPoint pointA, QPoint pointB);
	static const int clamp(int value);
};