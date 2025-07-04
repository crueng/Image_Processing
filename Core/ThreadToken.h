#pragma once
#include "core_global.h"

#include <atomic>

enum
{
	Enabled = true,
	Disabled = false
};

class CORE_EXPORT ThreadToken
{
public:
	//Constructs the token with default value true
	ThreadToken();
	~ThreadToken() = default;

	//Sets the token
	bool getToken()const;

	//Returns the token
	void setToken(bool value);
	
private:
	std::atomic<bool> m_token;
};