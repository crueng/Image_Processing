#include "doctest.h"
#include "Core/Image_Filter_BW.h"
#include "Core/Image_Filter_ColorCorrection.h"
#include "Core/Image_Filter_Vignette.h"

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
	}
}