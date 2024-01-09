//
// Created by vladimir on 09.01.24.
//

#pragma once
#include <vector>
//#include <thread>
#include <atomic>
#include <functional>
#include "ThreadSafeQueue.h"

class ThreadPool {
public:
    explicit ThreadPool(std::size_t num_threads){
        for(std::size_t i =0; i < num_threads;++i)
            threads.push_back(std::thread{[this]{
                while(!is_done){
                    std::function<void()> task;
                    if(queue_.Get_task(task))
                        task();
                    else
                        std::this_thread::yield();
                }
            }});
    }

    void submit(){
        queue_.Add_task(&Task);
    }
    ~ThreadPool(){
        is_done = true;
    }


private:
    std::atomic<bool> is_done = false;
    ThreadSafeQueue<std::function<void()>> queue_;
    std::vector<std::thread> threads;
};


