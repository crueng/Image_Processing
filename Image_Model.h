#pragma once
#include <stack>
#include <QImage>
#include <vector>
#include <string>

class Image_Model
{
public:
	void addImage(QImage image);
	void addFilter(std::string filterName);
	QImage getTop();
	bool empty();
private:
	std::stack<QImage> m_imageStack;
	std::vector<std::string> m_filter;
};

