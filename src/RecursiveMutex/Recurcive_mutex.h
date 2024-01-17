//
// Created by vladimir on 17.01.24.
//

#pragma once
#include <thread>
#include <atomic>
#include <mutex>

class Recursive_mutex {
public:
    Recursive_mutex();
    ~Recursive_mutex();
    void lock();

    bool try_lock();

    void unlock();

private:
    std::atomic<int> count_lock;
    std::thread::id thread_id;
    std::mutex mute;
};


