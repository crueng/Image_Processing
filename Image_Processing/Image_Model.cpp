#include "Image_Model.h"

void Image_Model::addImage(QImage image)
{
	m_imageStack.push(image);
}

void Image_Model::addFilter(std::string filterName)
{
	m_filter.push_back(filterName);
}

QImage Image_Model::getTop()
{
	if (m_imageStack.empty())
	{
		QImage emptyImage;
		return emptyImage;
	}
	QImage img = m_imageStack.top();
	m_imageStack.pop();
	return img;
}

bool Image_Model::empty()
{
	return m_imageStack.empty();
}
