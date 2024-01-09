//
// Created by vladimir on 09.01.24.
//

#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std::chrono_literals;
void Task(){
    std::this_thread::sleep_for(10ms);
}

template <typename T>
class ThreadPool {
public:
    ThreadPool() = default;
    void Add_task(T* val);

    T Get_task();

private:
    std::queue<T> tasks;
    mutable std::mutex mute;
    std::condition_variable queue_cv;
};

template<typename T>
T ThreadPool<T>::Get_task() {
    std::unique_lock<std::mutex> queue_lock(mute);
    queue_cv.wait(queue_lock, [&]{return !tasks.empty();});
    T out = tasks.front();
    tasks.pop();
    return out;
}

template<typename T>
void ThreadPool<T>::Add_task(T* val) {
    std::lock_guard lock(mute);
    tasks.push(val);
    queue_cv.notify_one();
}


