#pragma once
#include "Image_Filter.h"
#include "Filter_Factory.h"

#include <QImage>
#include <QPoint>

class Image_Filter_Vignette : public Image_Filter
{
public:
	Image_Filter_Vignette() = default;
	~Image_Filter_Vignette() override = default;
	void applyFilter(QImage& img) override;
	const int clamp(const int value);
	int getDistance(QPoint pointA, QPoint pointB);
};

