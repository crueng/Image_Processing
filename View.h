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
	void setImage(QImage px);

	//returns the labelSize
	const QSize getLabelSize() const;

	//Returns the current Image
	QImage& getImage();

	//Sets the text and duration of the status bar
	void setStatusBar(const QString message, int duration);

	//Sets the text of the Image_Path_Line
	void setImagePathLine(const QString message);

	//Sets the progressBar
	void setProgressBar(size_t value);

	//Creates a new QAction
	void createFilter(const QString filterName);

	//Enables the cancel button
	void enableCancelButton() const;

	//Shows the progressbar
	void showProgessBar();

	//Disables the cancel Button
	void disableCancelButton() const;

	//Hides the progressbar
	void hideProgressBar();

	void updateImage();
	
	signals:
	void bwFilterEnabled();
	void vignetteFilterEnabled();
	void colorCorrectionEnabled();
	void undoButtonpressed();
	void chooseFileButtonPressed();
	void cancelButtonPressed();
	void actionTriggered(QString func);

private:
	Ui::Image_ProcessingClass m_ui;
	QImage m_original;
};
