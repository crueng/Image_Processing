#include "Presenter.h"
#include <QString>
#include <QImage>

Presenter::Presenter(Image_Processing& v) : m_view(v)
{
	connect(&m_view, &Image_Processing::bwFilterEnabled, this, &Presenter::enableBWFilter);
	connect(&m_view, &Image_Processing::vignetteFilterEnabled, this, &Presenter::enableVignetteFilter);
}

void Presenter::enableBWFilter()
{
	QImage img = m_view.getImage();
	m_render.setBlackWhiteFilter(img);
	QPixmap px = QPixmap::fromImage(img);
	m_view.setPixmap(px);
}

void Presenter::enableVignetteFilter()
{
	QImage img = m_view.getImage();
	m_render.setVignetteFilter(img);
	QPixmap px = QPixmap::fromImage(img);
	m_view.setPixmap(px);
}
