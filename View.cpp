#include "View.h"
#include <QFileDialog>

Image_Processing::Image_Processing(QWidget* parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);
	connectPresenter();
}

Image_Processing::~Image_Processing()
{}



void Image_Processing::connectPresenter()
{
	connect(m_ui.Choose_Image_Button, &QPushButton::pressed, this, &Image_Processing::chooseFile);
}

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
