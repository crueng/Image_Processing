#include "Image_Renderer.h"
#include <QSize>
#include <QPainter>
#include <QPoint>
#include <QColor>
#include <chrono>
#include <qDebug>
#include <QtMath>

#define CURRENT_TIME std::chrono::high_resolution_clock::now()
void Image_Renderer::setBlackWhiteFilter(QImage& img)
{
	auto startTime = CURRENT_TIME;
	QSize size = img.size();
	for (int y = 0; y < size.height(); y++)
	{
		for (int x = 0; x < size.width(); x++)
		{
			QColor color = img.pixelColor(x, y);
			int gray = qGray(color.rgb());
			img.setPixelColor(x, y, QColor(gray, gray, gray, color.alpha()));
		}
	}
	auto stopTime = CURRENT_TIME;
	double resultTime = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count();
	qDebug() << "Time in ms: " << resultTime;
}

void Image_Renderer::setVignetteFilter(QImage& img)
{
	const QSize size = img.size();
	const QPoint center(size.width() / 2, size.height() / 2);
	for (int y = 0; y < size.height(); y++)
	{
		for (int x = 0; x < size.width(); x++)
		{
			QColor color = img.pixelColor(x, y);
			QPoint point(x, y);
			int distance = getDistance(center, point);
			int grayScale = ((double)distance / (size.width() / 2)) * 100;
			if (grayScale < 0)
			{
				grayScale = 0;
			}
			if (grayScale > 100)
			{
				grayScale = 100;
			}
			img.setPixelColor(x, y, QColor(
				clamp(color.red() * std::abs(grayScale - 100) / 100),
				clamp(color.green() * std::abs(grayScale - 100) / 100),
				clamp(color.blue() * std::abs(grayScale - 100) / 100)));
		}
	}
}

const int Image_Renderer::getDistance(QPoint pointA, QPoint pointB)
{
	const int a = qAbs(pointA.x() - pointB.x());
	const int b = qAbs(pointA.y() - pointB.y());
	const int cSquare = (qPow(a, 2)) + (qPow(b, 2));
	const int c = (qSqrt(cSquare));
	return c;
}

const int Image_Renderer::clamp(int value)
{
	if (value < 0)
	{
		return 0;
	}
	if (value > 255)
	{
		return 255;
	}
	return value;
}
