#pragma once
#include "ThreadToken.h"

#include <QImage>
#include <QObject>

class Image_Filter : public QObject
{
	Q_OBJECT

signals:
	void updatePercentage();
	void changeImage(QImage img);

public:
	virtual ~Image_Filter() = default;

	//Applies the filter to the image
	virtual void applyFilter(QImage& img) = 0;

	//Sets the token of the filter
	virtual void setToken(ThreadToken& token) = 0;
};