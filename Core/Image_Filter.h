#pragma once
#include "ThreadToken.h"
#include "core_global.h"

#include <QImage>
#include <QObject>

class CORE_EXPORT Image_Filter : public QObject
{
	Q_OBJECT

signals:
	void updatePercentage(int count);
	void changeImage(QImage img);

public:
	virtual ~Image_Filter() = default;

	//Applies the filter to the image
	virtual void applyFilter(QImage& img) = 0;

	//Sets the token of the filter
	virtual void setToken(ThreadToken& token) = 0;
};