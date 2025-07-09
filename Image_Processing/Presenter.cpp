#include "Presenter.h"
#include "Core/PluginLoader.h"

#include <QString>
#include <QImage>
#include <QFileDialog>
#include <chrono>
#include <QDebug>
#include <memory>
#include <mutex>

namespace
{
	const int STATUS_BAR_DURATION = 2000;
}

Q_DECLARE_METATYPE(size_t);

Presenter::Presenter(Image_Processing& v) : m_view(v)
{
	qRegisterMetaType<size_t>("size_t");
	loadExternFilter();
	//loadFilter();
	//Connects the presenter with the view
	connect(&m_view, &Image_Processing::actionTriggered, this, &Presenter::handleAction);
	connect(&m_view, &Image_Processing::undoButtonpressed, this, &Presenter::handleUndoButton);
	connect(&m_view, &Image_Processing::chooseFileButtonPressed, this, &Presenter::handleChooseFile);
	connect(&m_view, &Image_Processing::cancelButtonPressed, this, &Presenter::handleCancelButton);

	//Connects the thread
	connect(this, &Presenter::threadFinished, this, &Presenter::handleFinishedThread, Qt::QueuedConnection);
	//connect(this, &Presenter::setProgressbarPercentage, this, &Presenter::setProgress, Qt::QueuedConnection);

	loadImage(":/resources/Natur.jpg");
}

Presenter::~Presenter()
{
	//Waits for the thread to finish
	if (m_workerThread->joinable())
	{
		m_workerThread->join();
	}
}

void Presenter::loadFilter()
{
	//Initializes the filter in the model and creates QActions in the view 
	for (const auto& [filter, index] : Filter_Factory::instance().m_type)
	{
		m_model.addFilter(filter);
		m_view.createFilter(filter.c_str());
	}
}

void Presenter::handleUndoButton()
{
	//If the model is empty show "No Image Selected"
	if (m_model.empty())
	{
		m_view.setImagePathLine("No Image Selected");
	}
	//Else set the Pixmap to the last image
	m_view.setImage(m_model.getTop());
	m_view.setStatusBar("Undo", STATUS_BAR_DURATION);
}

void Presenter::handleChooseFile()
{
	//Get the path to your Image
	QString path = QFileDialog::getOpenFileName(&m_view, "Choose Image", "", "Bilder (*.png *.jpg *.jpeg)");
	if (!path.isEmpty())
	{
		//If the workerThread is still running, wait for it
		if (m_workerThread != nullptr)
		{
			if (m_workerThread->joinable())
			{
				m_workerThread->join();
			}
		}
		//The workerThread starts to load the image
		m_workerThread = std::make_unique<std::thread>([this, path]()
			{
				loadImage(path);
			});
	}
	else
	{
		m_view.setStatusBar("Something went wrong", STATUS_BAR_DURATION);
	}
}

void Presenter::handleAction(QString name)
{
	m_token.setToken(Enabled);
	m_view.enableCancelButton();
	m_view.setProgressBar(0);
	m_view.showProgessBar();
	std::shared_ptr action = Filter_Factory::instance().createFilter(name);

	//Connects the percentage updater
	connect(action.get(), &Image_Filter::updatePercentage, this, &Presenter::incrementCounter, Qt::QueuedConnection);
	connect(action.get(), &Image_Filter::changeImage, this, &Presenter::updateImage, Qt::QueuedConnection);
	/*connect(action.get(), &Image_Filter::updatePercentage, this, [&](size_t percent)
	{
		QMetaObject::invokeMethod(&m_view, "setProgressBar", Q_ARG(size_t, percent));
	});*/

	QImage& img = m_view.getImage();
	m_model.addImage(img);
	auto process = [this, name, action, img = std::ref(img)]() mutable
		{
			action->setToken(m_token);
			const auto startTime = std::chrono::high_resolution_clock::now();
			action->applyFilter(img);
			qDebug() << "filter done";
			const auto stopTime = std::chrono::high_resolution_clock::now();
			const double resultTime = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count();
			const QString message = name + " applied |" + " " + "Time in ms: " + (std::to_string(resultTime)).c_str();
			emit threadFinished(std::move(img), std::move(message));
			//QMetaObject::invokeMethod(this, "handleFinishedThread", Q_ARG(QImage, img), Q_ARG(QString, message));
		};

	//If the workerThread is still running, wait for it
	if (m_workerThread != nullptr)
	{
		if (m_workerThread->joinable())
		{
			m_workerThread->join();
		}
	}
	m_counter = 0;
	//The workerThread starts to apply the filter
	m_workerThread = std::make_unique<std::thread>(std::move(process));
}

void Presenter::handleFinishedThread(QImage img, QString name)
{
	m_view.setImage(img);
	m_view.disableCancelButton();
	m_view.setStatusBar(name, STATUS_BAR_DURATION);
	m_view.hideProgressBar();
	qDebug() << m_counter;
}

void Presenter::handleCancelButton()
{
	qDebug() << "canceled";
	m_token.setToken(Disabled);
}

void Presenter::incrementCounter(int count)
{
	QImage img = m_view.getImage();
	int size = img.width() * img.height();
	m_counter += count;
	m_progress = std::round((float)m_counter / (float)size * 1000.0f);
	m_view.setProgressBar(m_progress);
	m_view.updateImage();
}

void Presenter::updateImage(QImage img)
{
	m_view.setImage(img);
}

void Presenter::loadImage(QString path)
{
	QImage image(path);
	image.convertTo(QImage::Format_RGBA8888);

	QMetaObject::invokeMethod(&m_view, [this, image, path]()
	{
		m_view.setImage(image);
		m_view.setStatusBar("File loaded", STATUS_BAR_DURATION);
		m_view.setImagePathLine(path);
	}, Qt::QueuedConnection);
}

void Presenter::loadExternFilter()
{
	PluginLoader loader;
	loader.loadPlugins();
	for (auto filter : loader.getExternFilter())
	{
		m_model.addFilter(filter);
		m_view.createFilter(filter.c_str());
	}
}