#include "Image_Filter_BW.h"

#include <thread>
#include <QDebug>

void Image_Filter_BW::applyFilter(QImage& img)
{

	int THREAD_QUANTITY = std::thread::hardware_concurrency();
	img.detach();
	std::vector<std::thread> activeThreads;
	int threadSize = (img.width() * img.height()) / THREAD_QUANTITY;
	int remaining = (img.width() * img.height()) % THREAD_QUANTITY;

	//Starts all the threads
	for (int i = 0; i < THREAD_QUANTITY; i++)
	{
		int startPosition = threadSize * i;
		int thisThreadSize = threadSize;
		if (i == THREAD_QUANTITY - 1)
		{
			thisThreadSize += remaining;
		}
		std::thread t([this, &img, thisThreadSize, startPosition]()
			{
				//qDebug() << "thread started";
				runFilterInThread(img, thisThreadSize, startPosition);
			});
		activeThreads.push_back(std::move(t));
	}

	//Waits for all the active threads
	for (int i = 0; i < activeThreads.size(); i++)
	{
		activeThreads[i].join();
	}
}

void Image_Filter_BW::setToken(ThreadToken& token)
{
	m_token = &token;
}

void Image_Filter_BW::runFilterInThread(QImage& img, int threadSize, int startPosition)
{
	uint32_t* data = reinterpret_cast<uint32_t*>(img.bits());

	int counter = 0;
	int total = img.width() * img.height();
	int threshold = total / 1000;
	for (int i = startPosition; i < startPosition + threadSize; i++)
	{
		counter++;
		if (counter % threshold == 0)
		{
			emit updatePercentage(threshold);
			//emit changeImage(img);
		}
		if (!m_token->getToken())
		{
			qDebug() << "thread done";
			break;
		}
		// get the pixel Color
		uint32_t pixelValue = data[i];
		int alpha = (pixelValue >> 24) & 0xFF;
		int blue = (pixelValue >> 16) & 0xFF;
		int green = (pixelValue >> 8) & 0xFF;
		int red = (pixelValue >> 0) & 0xFF;
		QColor color(red, green, blue, alpha);

		// modify the pixel Color
		int gray = qGray(color.rgb());
		QColor newColor(gray, gray, gray, color.alpha());

		// write back the new pixel color
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
