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
	QPainter painter(this);
	auto temp = m_img.scaled(contentsRect().size(), Qt::KeepAspectRatio);
	painter.drawImage(QRect(QPoint(), temp.size()), temp);
}