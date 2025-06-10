#include "Presenter.h"
#include <QString>

Presenter::Presenter(Image_Processing &v) : m_view(v)
{
	connectView();
}

Presenter::~Presenter()
{
}


void Presenter::connectView()
{
	
}