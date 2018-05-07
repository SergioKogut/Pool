#include<iostream> 
#include<thread>  
#include<string>
#include<chrono> 
#include<deque> 
#include <Windows.h>
#include <ostream>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <future>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include "SafeQueue.h"

using  std::cout;
using std::endl;
using std::promise;
using std::future;
using std::string;
using namespace std::chrono_literals;
using namespace std;


// клас, що  виконує фунцію приєднання всіх потоків 
	class join_threads
	{
		std::vector<std::thread>&threads;
	public :
		// конструктор (передаєм вектор потоків)
		explicit join_threads(std::vector<std::thread>&threads_) :
			threads(threads_){}
	// деструктор - приєднуємо всі потоки
		~join_threads()
	{
		for(unsigned long i = 0; i < threads.size(); ++i)
		{
			if(threads[i].joinable())
				threads[i].join();
		}
	}
	};


	// клас - пул потоків
	class ThreadPool
	{
		std::atomic_bool done;
		SafeQueue <function<void()>>work_queue;
		std::vector<std::thread> threads;
		join_threads joiner;

		void worker_thread()
		{
			while( !done) 
			{
				std::function<void()> task;
				if(/*work_queue.try_pop(task)*/true)
				{
					task(); 
				}
					else
				{
					std::this_thread::yield();
					
				}
			}
		}

	public:
		ThreadPool() :done(false), joiner(threads)
		{
			unsigned const thread_count = std::thread::hardware_concurrency();
			try
			{
				for (unsigned i = 0; i < thread_count; ++i)
				{
					threads.push_back(std::thread(&ThreadPool::worker_thread, this));
				}
			}
			catch (...)
			{
				done = true;
				throw;
			}
		}
		~ThreadPool()
		{
			done = true;
		}
		
		template<typename FunctionType>
		void submit(FunctionType f)
		{
			work_queue.push(std::funct ion<void()>(f));
		}
	};

	int main()
	{







	return 0;
	}

