#pragma once
#include "Image_Filter.h"
#include "Filter_Factory.h"
#include "ThreadToken.h"

#include <QObject>

class Image_Filter_ColorCorrection : public Image_Filter, public QObject
{
	Q_OBJECT
	
public:
	Image_Filter_ColorCorrection() = default;
	~Image_Filter_ColorCorrection() override = default;
	void applyFilter(QImage& img) override;
	void setToken(ThreadToken& token) override;
	const int clamp(const int value);
private:
	ThreadToken* m_token;
};