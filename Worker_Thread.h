#pragma once
#include <QThread>
#include <functional>
#include <memory>

template <typename T>
class Worker_Thread
{
public:
	Worker_Thread(std::function<T> func)
	{
		workerThread = std::make_unique<QThread>(func);
	}

private:
	~Worker_Thread()
	{
		workerThread->quit();
	}
	std::unique_ptr<QThread> workerThread;
};