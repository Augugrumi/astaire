//
// Created by zanna on 13/09/18.
//

#ifndef ASTAIRE_THREADPOOL_H
#define ASTAIRE_THREADPOOL_H

#if !(HAS_BOOST_THREAD)

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

namespace utils {

    class ThreadPool {
        public:
            ThreadPool(size_t);
            template<class F, class... Args>
            auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
            ~ThreadPool();
        private:
            // need to keep track of threads so we can join them
            std::vector< std::thread > workers;
            // the task queue
            std::queue< std::function<void()> > tasks;

            // synchronization
            std::mutex queue_mutex;
            std::condition_variable condition;
            bool stop;
    };

}// namespace utils

#endif

#endif //ASTAIRE_THREADPOOL_H
