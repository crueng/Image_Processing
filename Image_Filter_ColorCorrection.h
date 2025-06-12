#pragma once
#include "Image_Filter.h"
#include "Filter_Factory.h"

class Image_Filter_ColorCorrection : public Image_Filter
{
public:
	Image_Filter_ColorCorrection() = default;
	~Image_Filter_ColorCorrection() override = default;
	void applyFilter(QImage& img) override;
	const int clamp(const int value);
};

