#include "Image_Filter_Vignette.h"
#include <QtMath>

void Image_Filter_Vignette::applyFilter(QImage& img)
{
	const QSize size = img.size();
	const QPoint center(size.width() / 2, size.height() / 2);
	const int maxDistance = getDistance(center, QPoint(0, 0));
	img.detach();
	img.convertTo(QImage::Format_RGBA8888);

	uint32_t* data = reinterpret_cast<uint32_t*>(img.bits());
	int counter = 0;
	int total = img.width() * img.height();
	int threshold = total / 1000;
#pragma omp parallel for
	for (int64_t i = 0; i < size.width() * size.height(); i++)
	{
		if (!m_token->getToken())
		{
			break;
		}
		counter++;
		if (counter % threshold == 0)
		{
			emit updatePercentage(threshold);
		}
		int x = i % size.width();
		int y = i / size.width();

		uint32_t pixelValue = data[i];
		int alpha = (pixelValue >> 24) & 0xFF;
		int blue = (pixelValue >> 16) & 0xFF;
		int green = (pixelValue >> 8) & 0xFF;
		int red = (pixelValue >> 0) & 0xFF;
		QColor color(red, green, blue, alpha);

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

		QColor newColor(clamp(color.red() * std::abs(grayScale - 100) / 100),
			clamp(color.green() * std::abs(grayScale - 100) / 100),
			clamp(color.blue() * std::abs(grayScale - 100) / 100));

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

void Image_Filter_Vignette::setToken(ThreadToken& token)
{
	m_token = &token;
}

const int Image_Filter_Vignette::clamp(const int value)
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

int Image_Filter_Vignette::getDistance(QPoint pointA, QPoint pointB)
{

	const int a = qAbs(pointA.x() - pointB.x());
	const int b = qAbs(pointA.y() - pointB.y());
	const int cSquare = (qPow(a, 2)) + (qPow(b, 2));
	const int c = (qSqrt(cSquare));
	return c;
}

namespace
{
	class Starter
	{
	public:
		Starter()
		{
			Filter_Factory::instance().m_vec.push_back([]()
				{
					return std::make_unique<Image_Filter_Vignette>();
				});
			Filter_Factory::instance().m_type["Vignette"] = Filter_Factory::instance().m_vec.size() - 1;
		}

		~Starter() = default;
	};

	Starter RegisterVignetteFilter;
}