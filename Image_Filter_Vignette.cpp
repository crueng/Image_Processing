#include "Image_Filter_Vignette.h"
#include <QtMath>

void Image_Filter_Vignette::applyFilter(QImage& img)
{
	const QSize size = img.size();
	const QPoint center(size.width() / 2, size.height() / 2);
	const int maxDistance = getDistance(center, QPoint(0, 0));
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