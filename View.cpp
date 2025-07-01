#include "View.h"
#include <QFileDialog>

Image_Processing::Image_Processing(QWidget* parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);
	QPixmap px;
	m_ui.Image_Label->setPixmap(px);
	m_ui.Image_ProgressBar->setMinimum(0);
	m_ui.Image_ProgressBar->setMaximum(1000);
	hideProgressBar();
	disableCancelButton();

	//Connects QActions with Presenter
	connect(m_ui.openImage, &QAction::triggered, this, &Image_Processing::chooseFileButtonPressed);
	connect(m_ui.BW_Filter, &QAction::triggered, this, &Image_Processing::bwFilterEnabled);
	connect(m_ui.Vignette_Filter, &QAction::triggered, this, &Image_Processing::vignetteFilterEnabled);
	connect(m_ui.Color_Correction, &QAction::triggered, this, &Image_Processing::colorCorrectionEnabled);

	//Connects QPushButtons with Presenter
	connect(m_ui.Undo_Button, &QPushButton::pressed, this, &Image_Processing::undoButtonpressed);
	connect(m_ui.Cancel_Button, &QPushButton::pressed, this, &Image_Processing::cancelButtonPressed);
}

Image_Processing::~Image_Processing()
{}

void Image_Processing::setImage(QImage px)
{
	m_original = px;
	m_ui.Image_Label->setPixmap(QPixmap::fromImage(px.scaled(m_ui.Image_Label->size(), Qt::KeepAspectRatio)));
}

const QSize Image_Processing::getLabelSize() const
{
	return m_ui.Image_Label->size();
}

QImage Image_Processing::getImage()
{
	return m_original;
}

void Image_Processing::setStatusBar(const QString message, int duration)
{
	m_ui.statusBar->showMessage(message, duration);
}

void Image_Processing::setImagePathLine(const QString message)
{
	m_ui.Image_Path_Line->setText(message);
}

void Image_Processing::setProgressBar(size_t value)
{
	if (value > 1000)
	{
		value = 1000;
	}
	m_ui.Image_ProgressBar->setValue(value);
	//m_ui.Image_ProgressBar->update();
}

void Image_Processing::createFilter(const QString filterName)
{
	auto* action = m_ui.menuFilter->addAction(filterName);
	connect(action, &QAction::triggered, this, [this, filterName]()
	{
		emit actionTriggered(filterName);
	});
}

void Image_Processing::enableCancelButton() const
{
	m_ui.Cancel_Button->setEnabled(true);
	m_ui.Cancel_Button->show();
}

void Image_Processing::showProgessBar()
{
	m_ui.Image_ProgressBar->show();
}

void Image_Processing::disableCancelButton() const
{
	m_ui.Cancel_Button->setEnabled(false);
	m_ui.Cancel_Button->hide();
}

void Image_Processing::hideProgressBar()
{
	m_ui.Image_ProgressBar->hide();
}
