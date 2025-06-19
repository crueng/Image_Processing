#pragma once
#include "View.h"
#include "Image_Model.h"
#include "Filter_Factory.h"

#include <QObject>

class Presenter : public QObject
{
	Q_OBJECT
public:
	Presenter(Image_Processing &v);
	void loadFilter();
public slots:
	void handleUndoButton();
	void handleChooseFile();
	void handleAction(QString name);
private:
	Image_Processing& m_view;
	Image_Model m_model;
};