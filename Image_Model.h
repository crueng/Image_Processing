#pragma once
#include <stack>
#include <QImage>

class Image_Model
{
public:
	void add(QImage image);
	QImage getTop();
private:
	std::stack<QImage> m_imageStack;
};

