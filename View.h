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

	//Sets the pixmap on the label
	void setPixmap(QPixmap px);

	//returns the labelSize
	const QSize getLabelSize() const;

	//Returns the current Image
	QImage getImage();

	//Sets the text and duration of the status bar
	void setStatusBar(const QString message, int duration);
	
	signals:
	void bwFilterEnabled();
	void vignetteFilterEnabled();
	void colorCorrectionEnabled();
	void undoButtonpressed();
	void chooseFileButtonPressed();

private:
	Ui::Image_ProcessingClass m_ui;
};
