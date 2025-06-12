#include "Presenter.h"
#include "Worker_Thread.h"

#include <QString>
#include <QImage>
#include <QFileDialog>

#define STATUS_BAR_DURATION 2000

Presenter::Presenter(Image_Processing& v) : m_view(v)
{
	loadFilter();
	//connect(&m_view, &Image_Processing::bwFilterEnabled, this, &Presenter::enableBWFilter);
	//connect(&m_view, &Image_Processing::vignetteFilterEnabled, this, &Presenter::enableVignetteFilter);
	//connect(&m_view, &Image_Processing::colorCorrectionEnabled, this, &Presenter::enableColorCorrection);
	connect(&m_view, &Image_Processing::actionTriggered, this, &Presenter::handleAction);
	connect(&m_view, &Image_Processing::undoButtonpressed, this, &Presenter::handleUndoButton);
	connect(&m_view, &Image_Processing::chooseFileButtonPressed, this, &Presenter::handleChooseFile);
}

void Presenter::loadFilter()
{
	for (const auto& [filter, index] : Filter_Factory::instance().m_type)
	{
		m_model.addFilter(filter);
		m_view.createFilter(filter.c_str());
	}
}

void Presenter::handleUndoButton()
{
	if (m_model.empty())
	{
		m_view.setImagePathLine("No Image Selected");
	}
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
		m_view.setImagePathLine(path);
	}
	else
	{
		m_view.setStatusBar("Something went wrong", STATUS_BAR_DURATION);
	}
}

void Presenter::handleAction(QString name)
{
	openThread(name);
}

void Presenter::openThread(QString name)
{
	auto action = Filter_Factory::instance().createFilter(name);
	QImage img = m_view.getImage();
	m_model.addImage(img);
	auto func = [&]()
	{
		action->applyFilter(img);
		return 0;
	};
	std::thread t(func);
	t.join();
	m_view.setPixmap(QPixmap::fromImage(img));
	QString message = name + " applied";
	m_view.setStatusBar(message, STATUS_BAR_DURATION);
}