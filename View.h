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

	//Opens the Windows file explorer and you can choose an image
	void chooseFile();

	//Sets the pixmap on the label
	void setPixmap(QPixmap px);

	//returns the labelSize
	const QSize getLabelSize() const;

	QImage getImage();

	signals:
	void bwFilterEnabled();
	void vignetteFilterEnabled();

private:
	void connectPresenter();
	Ui::Image_ProcessingClass m_ui;
};
