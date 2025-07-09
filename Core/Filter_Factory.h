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

#define REGISTER_FILTER(CLASS, UI_LABEL) namespace \
{\
	class Starter\
	{\
	public:\
		Starter()\
		{\
			Filter_Factory::instance().m_vec.push_back([]()\
				{\
					return std::make_unique<CLASS>();\
				});\
			\
			Filter_Factory::instance().m_type[UI_LABEL] = Filter_Factory::instance().m_vec.size() - 1;\
		}\
		\
		~Starter() = default;\
	};\
	\
	Starter RegisterBWFilter;\
}