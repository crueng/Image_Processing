#include "doctest.h"
#include "Core/Image_Filter_BW.h"
#include "Core/Image_Filter_ColorCorrection.h"
#include "Core/Image_Filter_Vignette.h"

#include <QtMath>
namespace
{
	int rgbClamp(int rgb)
	{
		if (rgb > 255)
		{
			return 255;
		}
		if (rgb < 0)
		{
			return 0;
		}
		return rgb;
	}

	int grayScaleClamp(int grayScale)
	{
		if (grayScale > 100)
		{
			return 100;
		}
		if (grayScale < 0)
		{
			return 0;
		}
		return grayScale;
	}

	int getDistance(QPoint pointA, QPoint pointB)
	{
		const int a = qAbs(pointA.x() - pointB.x());
		const int b = qAbs(pointA.y() - pointB.y());
		const int cSquare = (qPow(a, 2)) + (qPow(b, 2));
		const int c = (qSqrt(cSquare));
		return c;
	}
}

TEST_SUITE("Filter Tests")
{
	TEST_CASE("Filter_BW")
	{
		auto filter = Filter_Factory::instance().createFilter("Black White");
		ThreadToken token;
		filter->setToken(token);
		QSize imageSize(100, 100);
		QImage img(imageSize, QImage::Format_RGBA8888);
		img.fill(Qt::white);

		for (int y = 0; y < img.height(); y++)
		{
			for (int x = 0; x < img.width(); x++)
			{
				if (x % 2 == 0)
				{
					QColor color(120, 60, 40);
					img.setPixelColor(x, y, color);
					continue;
				}
				QColor color(180, 90, 220);
				img.setPixelColor(x, y, color);
			}
		}
		filter->applyFilter(img);
		for (int y = 0; y < img.height(); y++)
		{
			for (int x = 0; x < img.width(); x++)
			{
				if (x % 2 == 0)
				{
					int gray = qGray(img.pixelColor(x, y).rgb());
					QColor color(gray, gray, gray);
					CHECK(img.pixelColor(x, y) == color);
					continue;
				}
				int gray = qGray(img.pixelColor(x, y).rgb());
				QColor color(gray, gray, gray);
				CHECK(img.pixelColor(x, y) == color);
			}
		}
	}

	TEST_CASE("Filter_ColorCorrection")
	{
		auto filter = Filter_Factory::instance().createFilter("Color Correction");
		ThreadToken token;
		filter->setToken(token);
		QSize imageSize(100, 100);
		QImage img(imageSize, QImage::Format_RGBA8888);
		for (int y = 0; y < img.height(); y++)
		{
			for (int x = 0; x < img.width(); x++)
			{
				if (x % 2 == 0)
				{
					QColor color(120, 60, 40);
					img.setPixelColor(x, y, color);
					continue;
				}
				QColor color(180, 90, 220);
				img.setPixelColor(x, y, color);
			}
		}
		filter->applyFilter(img);
		for (int y = 0; y < img.height(); y++)
		{
			for (int x = 0; x < img.width(); x++)
			{
				if (x % 2 == 0)
				{
					QColor color(rgbClamp(120 * 0.8), rgbClamp(60 * 1.1), rgbClamp(40 * 1.1));
					CHECK(img.pixelColor(x, y).rgb() == color.rgb());
					continue;
				}
				QColor color(rgbClamp(180 * 0.8), rgbClamp(90 * 1.1), rgbClamp(220 * 1.1));
				CHECK(img.pixelColor(x, y).rgb() == color.rgb());
			}
		}
	}

	TEST_CASE("Filter_Vignette")
	{
		auto filter = Filter_Factory::instance().createFilter("Vignette");
		ThreadToken token;
		filter->setToken(token);
		QSize imageSize(100, 100);
		QImage img(imageSize, QImage::Format_RGBA8888);
		img.fill(Qt::white);
		QImage compareImage = img;
		filter->applyFilter(compareImage);

		const QPoint center(img.width() / 2, img.height() / 2);
		uint32_t* data = reinterpret_cast<uint32_t*>(img.bits());

		for (int64_t i = 0; i < img.width() * img.height(); i++)
		{
			int x = i % img.width();
			int y = i / img.width();

			uint32_t pixelValue = data[i];
			int alpha = (pixelValue >> 24) & 0xFF;
			int blue = (pixelValue >> 16) & 0xFF;
			int green = (pixelValue >> 8) & 0xFF;
			int red = (pixelValue >> 0) & 0xFF;
			QColor color(red, green, blue, alpha);

			QPoint point(x, y);

			int distance = getDistance(center, point);
			int grayScale = ((double)distance / (img.width() / 2)) * 100;
			grayScale = grayScaleClamp(grayScale);

			QColor newColor(rgbClamp(color.red() * std::abs(grayScale - 100) / 100),
				rgbClamp(color.green() * std::abs(grayScale - 100) / 100),
				rgbClamp(color.blue() * std::abs(grayScale - 100) / 100));
			CHECK(compareImage.pixelColor(x, y) == newColor);
		}
	}
}