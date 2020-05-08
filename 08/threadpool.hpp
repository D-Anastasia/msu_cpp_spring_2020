#ifndef pr_8
#define pr_8
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <mutex>
#include <atomic>
#include <future>
#include <condition_variable>

using namespace std;



class ThreadPool
{
	std::queue<std::function<void()>> Queue;
	std::vector<std::thread> threads;
	std::mutex m;
	size_t size;
	std::condition_variable condition;
	std::atomic<bool> end;
public:
	explicit ThreadPool(size_t poolSize){
		size = poolSize;
		end = false;
		for(int i = 0; i < size; i++) {
			threads.emplace_back([this] {
				while(!end) {
					std::unique_lock<std::mutex> lock(m);
					if(Queue.size() == 0) {
						condition.wait(lock);
					} else {
						auto task = move(Queue.front());
						Queue.pop();
						lock.unlock();
						task();
					}
				} 
			});
		}
	}
	 // pass arguments by value
	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
		using return_type = decltype( func(args...) );
		auto task = std::make_shared<std::packaged_task<return_type ()>>([func, args...](){
			return func(args...);
		});
		std::lock_guard<std::mutex> lock(m);
		Queue.emplace(
			[task]() {
				(*task)();
			});
		condition.notify_one();
		return task->get_future();
	}


	~ThreadPool() {
		condition.notify_all();
		end = true;
		for(int i = 0; i < size; i++) {
			threads[i].join();
		}
	}
};



#endif