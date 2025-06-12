#include "View.h"
#include <QFileDialog>

Image_Processing::Image_Processing(QWidget* parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);
	QPixmap px;
	m_ui.Image_Label->setPixmap(px);
	connect(m_ui.openImage, &QAction::triggered, this, &Image_Processing::chooseFileButtonPressed);
	connect(m_ui.BW_Filter, &QAction::triggered, this, &Image_Processing::bwFilterEnabled);
	connect(m_ui.Vignette_Filter, &QAction::triggered, this, &Image_Processing::vignetteFilterEnabled);
	connect(m_ui.Color_Correction, &QAction::triggered, this, &Image_Processing::colorCorrectionEnabled);
	connect(m_ui.Undo_Button, &QPushButton::pressed, this, &Image_Processing::undoButtonpressed);
}

Image_Processing::~Image_Processing()
{}

void Image_Processing::setPixmap(QPixmap px)
{
	m_ui.Image_Label->setPixmap(px);
}

const QSize Image_Processing::getLabelSize() const
{
	return m_ui.Image_Label->size();
}

QImage Image_Processing::getImage()
{
	QImage img = (m_ui.Image_Label->pixmap())->toImage();
	return img;
}

void Image_Processing::setStatusBar(const QString message, int duration)
{
	m_ui.statusBar->showMessage(message, duration);
}

void Image_Processing::setImagePathLine(const QString message)
{
	m_ui.Image_Path_Line->setText(message);
}

void Image_Processing::createFilter(const QString filterName)
{
	auto* action = m_ui.menuFilter->addAction(filterName);
	connect(action, &QAction::triggered, this, [this, filterName]()
	{
		emit actionTriggered(filterName);
	});
}