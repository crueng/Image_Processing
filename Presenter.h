#pragma once
#include <QObject>
#include "Image_Renderer.h"
#include "View.h"
#include "Image_Model.h"

class Presenter : public QObject
{
	Q_OBJECT
public:
	Presenter(Image_Processing &v);
public slots:
	void enableBWFilter();
	void enableVignetteFilter();
	void enableColorCorrection();
	void handleUndoButton();
	void handleChooseFile();
private:
	Image_Processing& m_view;
	Image_Renderer m_render;
	Image_Model m_model;
};