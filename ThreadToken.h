#pragma once
#include <atomic>

enum
{
	Enabled = true,
	Disabled = false
};

class ThreadToken
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