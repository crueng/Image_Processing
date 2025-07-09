#include "PluginLoader.h"
#include "Filter_Factory.h"
#include "Image_Filter.h"

#include <QLibrary>
#include <QDir>
#include <QDirIterator>

using filter = Filter_Factory(*)();

void PluginLoader::loadPlugins()
{
	QDir pluginPath("Plugins");
	QDirIterator iterator(pluginPath);
	for (auto file : pluginPath.entryList(QStringList() << "*.dll", QDir::Files))
	{
		QLibrary lib("Plugins\\" + file);
		if (!lib.load())
		{
			__debugbreak();
			return;
		}
		filter f = (filter)lib.resolve("getFactory");
		if (f)
		{
			for (auto& [filter, index] : f().m_type)
			{
				m_pluginFilter.push_back(filter);
			}
			return;
		}
		__debugbreak();
	}
}

std::vector<std::string> PluginLoader::getExternFilter()
{
	return m_pluginFilter;
}