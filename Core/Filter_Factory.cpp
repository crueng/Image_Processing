#include "Filter_Factory.h"

Filter_Factory& Filter_Factory::instance()
{
	static Filter_Factory factory;
	return factory;
}

std::unique_ptr<Image_Filter> Filter_Factory::createFilter(QString name)
{
	const int index = instance().m_type[name.toStdString()]; //Es wird ein Index zurückgegeben der identisch mit dem des Vectors "m_vec" ist
	const std::function<std::unique_ptr<Image_Filter>()> func = instance().m_vec[index]; //Die funktion an dem Index "index" wird func zugewiesen
	return func();
}
