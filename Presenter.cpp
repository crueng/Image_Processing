#include "Presenter.h"

#include <QString>
#include <QImage>
#include <QFileDialog>
#include <chrono>

#define STATUS_BAR_DURATION 2000

Presenter::Presenter(Image_Processing& v) : m_view(v)
{
	loadFilter();
	connect(&m_view, &Image_Processing::actionTriggered, this, &Presenter::handleAction);
	connect(&m_view, &Image_Processing::undoButtonpressed, this, &Presenter::handleUndoButton);
	connect(&m_view, &Image_Processing::chooseFileButtonPressed, this, &Presenter::handleChooseFile);
}

Presenter::~Presenter()
{
	m_workerThread->join();
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
	auto process = [this, name]()
		{
			m_view.enableCancelButton();
			const auto action = Filter_Factory::instance().createFilter(name);
			QImage img = m_view.getImage();
			m_model.addImage(img);
			const auto startTime = std::chrono::high_resolution_clock::now();
			action->applyFilter(img);
			const auto stopTime = std::chrono::high_resolution_clock::now();
			const double resultTime = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count();
			m_view.setPixmap(QPixmap::fromImage(img));
			m_view.disableCancelButton();
			const QString message = name + " applied |" + " " + "Time in ms: " + (std::to_string(resultTime)).c_str();
			m_view.setStatusBar(message, 2000);
		};
	if (m_workerThread != nullptr)
	{
		if (m_workerThread->joinable())
		{
			m_workerThread->join();
		}
	}
	m_workerThread = std::make_unique<std::thread>(process);
}