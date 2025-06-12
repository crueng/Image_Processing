#include "Image_Filter_BW.h"

void Image_Filter_BW::applyFilter(QImage& img)
{
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
				return std::make_unique<Image_Filter_BW>();
			});

			Filter_Factory::instance().m_type["Black White"] = Filter_Factory::instance().m_vec.size() - 1;
		}

		~Starter() = default;
	};

	Starter RegisterBWFilter;
}