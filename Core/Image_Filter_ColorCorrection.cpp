#include "Image_Filter_ColorCorrection.h"

#include <QColor>
#include <QSize>
#include <QImage>

REGISTER_FILTER(Image_Filter_ColorCorrection, "Color Correction")

void Image_Filter_ColorCorrection::applyFilter(QImage& img)
{
	img.detach();
	img.convertTo(QImage::Format_RGBA8888);

	QSize size = img.size();
	auto redMultiplier = [&](int value, double multiplier)
		{
			return clamp(value * multiplier);
		};
	auto greenMultiplier = [&](int value, double multiplier)
		{
			return clamp(value * multiplier);
		};
	auto  blueMultiplier = [&](int value, double multiplier)
		{
			return clamp(value * multiplier);
		};

	uint32_t* data = reinterpret_cast<uint32_t*>(img.bits());

	int counter = 0;
	int total = img.width() * img.height();
	int threshold = total / 1000;
#pragma omp parallel for
	for (int64_t i = 0; i < size.height() * size.width(); i++)
	{
		counter++;
		if (counter % threshold == 0)
		{
			emit updatePercentage(threshold);
		}
		
		if (!m_token->getToken())
		{
			break;
		}
		uint32_t pixelValue = data[i];

		int alpha = (pixelValue >> 24) & 0xFF;
		int blue = (pixelValue >> 16) & 0xFF;
		int green = (pixelValue >> 8) & 0xFF;
		int red = (pixelValue >> 0) & 0xFF;
		QColor color(red, green, blue, alpha);

		red = redMultiplier(red, 0.8);
		green = greenMultiplier(green, 1.1);
		blue = blueMultiplier(blue, 1.1);
		QColor newColor(red, green, blue, alpha);

		uint32_t newPixelValue = 0;
		newPixelValue = newPixelValue | (newColor.alpha() & 0xFF);
		newPixelValue <<= 8;
		newPixelValue = newPixelValue | (newColor.blue() & 0xFF);
		newPixelValue <<= 8;
		newPixelValue = newPixelValue | (newColor.green() & 0xFF);
		newPixelValue <<= 8;
		newPixelValue = newPixelValue | (newColor.red() & 0xFF);
		data[i] = newPixelValue;
	}
}

void Image_Filter_ColorCorrection::setToken(ThreadToken& token)
{
	m_token = &token;
}

const int Image_Filter_ColorCorrection::clamp(const int value)
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