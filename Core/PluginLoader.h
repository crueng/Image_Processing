#pragma once
#include "core_global.h"

#include <vector>
#include <string>

class CORE_EXPORT PluginLoader
{
public:
	void loadPlugins();
	std::vector<std::string> getExternFilter();
private:
	std::vector<std::string> m_dllPath;
	std::vector<std::string> m_pluginFilter;
};