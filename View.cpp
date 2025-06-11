#include "View.h"
#include <QFileDialog>

Image_Processing::Image_Processing(QWidget* parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);
	connect(m_ui.Choose_Image_Button, &QPushButton::pressed, this, &Image_Processing::chooseFile);
	connect(m_ui.BW_Filter, &QPushButton::pressed, this, &Image_Processing::bwFilterEnabled);
	connect(m_ui.Vignette_Filter, &QPushButton::pressed, this, &Image_Processing::vignetteFilterEnabled);
}

Image_Processing::~Image_Processing()
{}

void Image_Processing::chooseFile()
{
	QString path = QFileDialog::getOpenFileName(this, "Choose Image", "", "Bilder (*.png *.jpg *.jpeg)");
	if (!path.isEmpty())
	{
		QPixmap image(path);
		m_ui.Image_Label->setPixmap(image);
	}
}

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