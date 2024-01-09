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
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;
    void Add_task(T val);

    bool Get_task(T t);

private:
    std::queue<T> tasks;
    mutable std::mutex mute;
    std::condition_variable queue_cv;
};

template<typename T>
bool ThreadSafeQueue<T>::Get_task(T t) {
    if(tasks.empty())
        return false;
    std::unique_lock<std::mutex> queue_lock(mute);
    queue_cv.wait(queue_lock, [&]{return !tasks.empty();});
    t = tasks.front();
    tasks.pop();
    return true;
}

template<typename T>
void ThreadSafeQueue<T>::Add_task(T val) {
    std::lock_guard lock(mute);
    tasks.push(val);
    queue_cv.notify_one();
}


