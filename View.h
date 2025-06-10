#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Image_Processing.h"

#include <QString>
#include <QPixmap>

class Image_Processing : public QMainWindow
{
	Q_OBJECT

public:
	Image_Processing(QWidget* parent = nullptr);
	~Image_Processing();
	void chooseFile();
	void setPixmap(QPixmap px);

private:
	void connectPresenter();
	Ui::Image_ProcessingClass m_ui;
};
