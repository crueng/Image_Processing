#include "ThreadToken.h"

ThreadToken::ThreadToken()
{
	setToken(true);
}

bool ThreadToken::getToken() const
{
	return m_token.load();
}

void ThreadToken::setToken(bool value)
{
	m_token.store(value);
}
