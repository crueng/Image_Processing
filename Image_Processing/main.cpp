#include "View.h"
#include "Presenter.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Image_Processing w;
	Presenter p(w);
	w.show();
	return a.exec();
}