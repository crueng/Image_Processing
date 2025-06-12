#pragma once
#include <QImage>

class Image_Filter
{
public:
	virtual ~Image_Filter() = default;
	virtual void applyFilter(QImage& img) = 0;
};