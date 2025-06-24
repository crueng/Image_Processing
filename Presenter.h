#pragma once
#include "View.h"
#include "Image_Model.h"
#include "Filter_Factory.h"
#include "ThreadToken.h"

#include <QObject>
#include <memory>
#include <thread>

class Presenter : public QObject
{
	Q_OBJECT
public:
	Presenter(Image_Processing &v);
	~Presenter();
	void loadFilter();
public slots:
	void handleUndoButton();
	void handleChooseFile();
	void handleAction(QString name);
	void handleCancelButton();
private:
	Image_Processing& m_view;
	Image_Model m_model;
	std::unique_ptr<std::thread> m_workerThread;
};