#include "Presenter.h"
#include <QString>
#include <QImage>
#include <QFileDialog>

#define STATUS_BAR_DURATION 2000

Presenter::Presenter(Image_Processing& v) : m_view(v)
{
	connect(&m_view, &Image_Processing::bwFilterEnabled, this, &Presenter::enableBWFilter);
	connect(&m_view, &Image_Processing::vignetteFilterEnabled, this, &Presenter::enableVignetteFilter);
	connect(&m_view, &Image_Processing::colorCorrectionEnabled, this, &Presenter::enableColorCorrection);
	connect(&m_view, &Image_Processing::undoButtonpressed, this, &Presenter::handleUndoButton);
	connect(&m_view, &Image_Processing::chooseFileButtonPressed, this, &Presenter::handleChooseFile);
}

void Presenter::enableBWFilter()
{
	QImage img = m_view.getImage();
	m_model.add(img);
	m_render.setBlackWhiteFilter(img);
	QPixmap px = QPixmap::fromImage(img);
	m_view.setPixmap(px);
	m_view.setStatusBar("Black and White Filter applied", STATUS_BAR_DURATION);
}

void Presenter::enableVignetteFilter()
{
	QImage img = m_view.getImage();
	m_model.add(img);
	m_render.setVignetteFilter(img);
	QPixmap px = QPixmap::fromImage(img);
	m_view.setPixmap(px);
	m_view.setStatusBar("Vignette Filter applied", STATUS_BAR_DURATION);
}

void Presenter::enableColorCorrection()
{
	QImage img = m_view.getImage();
	m_model.add(img);
	m_render.setColorCorrection(img);
	QPixmap px = QPixmap::fromImage(img);
	m_view.setPixmap(px);
	m_view.setStatusBar("Color Correction applied", STATUS_BAR_DURATION);
}

void Presenter::handleUndoButton()
{
	m_view.setPixmap(QPixmap::fromImage(m_model.getTop()));
	m_view.setStatusBar("Undo", STATUS_BAR_DURATION);
}

void Presenter::handleChooseFile()
{
	QString path = QFileDialog::getOpenFileName(&m_view, "Choose Image", "", "Bilder (*.png *.jpg *.jpeg)");
	if (!path.isEmpty())
	{
		QPixmap image(path);
		m_view.setPixmap(image);
		m_view.setStatusBar("File loaded", STATUS_BAR_DURATION);
	}else
	{
		m_view.setStatusBar("Something went wrong", STATUS_BAR_DURATION);
	}
}
