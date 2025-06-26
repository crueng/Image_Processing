#pragma once
#include <stack>
#include <QImage>
#include <vector>
#include <string>

class Image_Model
{
public:
	//Adds an image to the stack
	void addImage(QImage image);

	//Pushs a filter to the vector
	void addFilter(std::string filterName);

	//Returns the top of the stack and pops the stack
	QImage getTop();

	//Checks if the stack is empty
	bool empty();
private:
	std::stack<QImage> m_imageStack;
	std::vector<std::string> m_filter;
};

