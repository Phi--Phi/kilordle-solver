#pragma once

#include <mutex>
#include <thread>
#include <queue>
#include <functional>

namespace kilordle
{
	class ThreadPool
	{
	public:
		ThreadPool(unsigned int Size);

		void AddTask(std::function<void()> Func);
		void StartPool();

		void Join();

		~ThreadPool();

	private:
		void RunThread(unsigned int Index);

		unsigned int ThreadCount;
		std::queue<std::function<void()>> TaskQueue;
		std::mutex QueueLock;
		std::vector<std::thread> Threads;
		std::vector<std::mutex*> ThreadLock;
		bool StopThreads;
	};
}