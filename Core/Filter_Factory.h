#pragma once
#include "Image_Filter.h"
#include "core_global.h"

#include <map>
#include <vector>
#include <memory>
#include <string>
#include <QString>

class CORE_EXPORT Filter_Factory
{
public:
	static Filter_Factory& instance();
	std::unique_ptr<Image_Filter> createFilter(QString name);
	std::map<std::string, int> m_type;
	std::vector<std::function<std::unique_ptr<Image_Filter>()>> m_vec;
};