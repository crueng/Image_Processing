#include "Image_Filter_ColorCorrection.h"

#include <QPoint>
#include <QColor>
#include <QSize>
#include <QImage>

void Image_Filter_ColorCorrection::applyFilter(QImage& img)
{
	QSize size = img.size();
	auto red = [&](int value, double multiplier)
		{
			return clamp(value * multiplier);
		};
	auto green = [&](int value, double multiplier)
		{
			return clamp(value * multiplier);
		};
	auto  blue = [&](int value, double multiplier)
		{
			return clamp(value * multiplier);
		};
	for (int y = 0; y < size.height(); y++)
	{
		for (int x = 0; x < size.width(); x++)
		{
			QPoint p(x, y);
			QColor color(img.pixelColor(p));
			img.setPixelColor(p, QColor(
				red(color.red(), 0.8),
				green(color.green(), 1.1),
				blue(color.blue(), 1.1)));
		}
	}
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

namespace
{
	class Starter
	{
	public:
		Starter()
		{
			Filter_Factory::instance().m_vec.push_back([]()
			{
				return std::make_unique<Image_Filter_ColorCorrection>();
			});

			Filter_Factory::instance().m_type["Color Correction"] = Filter_Factory::instance().m_vec.size() - 1;
		}

		~Starter() = default;
	};

	Starter RegisterColorCorrection;
}