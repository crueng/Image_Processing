#include "Image_Model.h"

void Image_Model::add(QImage image)
{
	m_imageStack.push(image);
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
