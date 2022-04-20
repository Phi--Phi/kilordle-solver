#include "ThreadPool.h"

kilordle::ThreadPool::ThreadPool(unsigned int Size)
{
	ThreadCount = Size;
	StopThreads = false;

	ThreadLock.resize(ThreadCount);
	Threads.reserve(ThreadCount);

	for (unsigned int Index = 0; Index < ThreadCount; Index++)
	{
		ThreadLock[Index] = new std::mutex;
		ThreadLock[Index]->lock();
		Threads.push_back(std::thread(&ThreadPool::RunThread, this, Index));
	}
}

void kilordle::ThreadPool::AddTask(std::function<void()> Func)
{
	QueueLock.lock();
	TaskQueue.push(Func);
	QueueLock.unlock();
}

void kilordle::ThreadPool::StartPool()
{
	for (unsigned int Index = 0; Index < ThreadCount; Index++)
	{
		ThreadLock[Index]->unlock();
	}
}

void kilordle::ThreadPool::Join()
{
	for (unsigned int Index = 0; Index < ThreadCount; Index++)
	{
		if (Threads[Index].joinable())
		{
			Threads[Index].join();
		}
	}
}

kilordle::ThreadPool::~ThreadPool()
{
	QueueLock.lock();
	StopThreads = true;
	QueueLock.unlock();

	for (unsigned int Index = 0; Index < ThreadCount; Index++)
	{
		if (Threads[Index].joinable())
		{
			Threads[Index].join();
		}
	}

	for (auto x : ThreadLock)
	{
		delete x;
	}
}

void kilordle::ThreadPool::RunThread(unsigned int Index)
{
	ThreadLock[Index]->lock();
	
	while (!StopThreads)
	{
		if (!QueueLock.try_lock())
		{
			continue;
		}

		if (TaskQueue.empty())
		{
			QueueLock.unlock();
			break;
		}

		std::function<void()> Task = TaskQueue.front();
		TaskQueue.pop();
		QueueLock.unlock();

		Task();
	}

	ThreadLock[Index]->unlock();
}
