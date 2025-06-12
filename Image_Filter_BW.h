#pragma once
#include "Filter_Factory.h"

#include <Image_Filter.h>

class Image_Filter_BW : public Image_Filter
{
public:
	Image_Filter_BW() = default;
	~Image_Filter_BW() override = default;

	void applyFilter(QImage& img) override;
};

