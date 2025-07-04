#pragma once
#include "Filter_Factory.h"
#include "ThreadToken.h"
#include "core_global.h"
#include "Image_Filter.h"

#include <QObject>

class CORE_EXPORT Image_Filter_BW : public Image_Filter
{
	Q_OBJECT
	
public:
	Image_Filter_BW() = default;
	~Image_Filter_BW() override = default;

	void applyFilter(QImage& img) override;
	void setToken(ThreadToken& token) override;
	void runFilterInThread(QImage& img, int threadSize, int startPosition);
private:
	ThreadToken* m_token;
};