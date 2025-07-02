#pragma once
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QWidget>

class UI_Image : public QWidget
{
	Q_OBJECT
public:
	void set(QImage img);
	QImage& get();
private:
	void paintEvent(QPaintEvent* event) override;
	QImage m_img;
};