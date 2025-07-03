#include "UI_Image.h"
void UI_Image::set(QImage img)
{
	m_img = std::move(img);
	update();
}

QImage& UI_Image::get()
{
	return m_img;
}

void UI_Image::paintEvent(QPaintEvent* event)
{
	QPoint topLeft(0,0);
	QRect rect(topLeft, m_img.size());
	QPainter painter(this);
	painter.drawImage(rect, m_img);
}