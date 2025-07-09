#pragma once
#include "Image_Filter.h"
#include "Filter_Factory.h"
#include "ThreadToken.h"
#include "core_global.h"

#include <QImage>
#include <QPoint>
#include <QObject>

class CORE_EXPORT Image_Filter_Vignette : public Image_Filter
{
	Q_OBJECT
	
public:
	Image_Filter_Vignette() = default;
	~Image_Filter_Vignette() override = default;
	void applyFilter(QImage& img) override;
	void setToken(ThreadToken& token) override;
	const int clamp(const int value);
	int getDistance(QPoint pointA, QPoint pointB);
private:
	ThreadToken* m_token;
};