#pragma once
#include "View.h"
#include "Image_Model.h"
#include "Filter_Factory.h"
#include "Image_Filter.h"

#include <QObject>
#include <memory>
#include <thread>

class Presenter : public QObject
{
	Q_OBJECT
public:
	Presenter(Image_Processing &v);
	~Presenter();

	signals:
	void threadFinished(QImage img, QString name);

	void setProgressbarPercentage(size_t value);
public slots:
	//Slot for the Undo Button
	void handleUndoButton();

	//Slot for the "Choose File" Button
	void handleChooseFile();

	//Slot for all the filter actions
	void handleAction(QString name);

	//Handles everything after the worker thread is finished
	void handleFinishedThread(QImage img, QString name);

	//Slot for the cancel Button
	void handleCancelButton();

	//Increments the counter
	void incrementCounter();

	//updates the image
	void updateImage(QImage img);
	
private:
	//Initializes the filters
	void loadFilter();
	
	Image_Processing& m_view;
	Image_Model m_model;
	std::unique_ptr<std::thread> m_workerThread;
	ThreadToken m_token;
	std::atomic<int> m_counter;
	std::atomic<int> m_progress;
};