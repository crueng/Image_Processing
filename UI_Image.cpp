#include "UI_Image.h"
void UI_Image::set(QImage img)
{
	m_img = img;
}

QImage& UI_Image::get()
{
	return m_img;
}

void UI_Image::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawRect(rect());
}