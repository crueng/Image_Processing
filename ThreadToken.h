#pragma once
#include <thread>
#include <memory>

class ThreadToken
{
public:
	void requestStop();
private:
	std::unique_ptr<std::thread> m_workerThread;
};