#pragma once
#include <QObject>
#include "View.h"

class Presenter : public QObject
{
	Q_OBJECT
public:
	Presenter(Image_Processing &v);
	~Presenter();
private:
	void connectView();
	Image_Processing& m_view;
};