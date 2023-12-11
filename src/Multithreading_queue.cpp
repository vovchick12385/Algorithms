//
// Created by vladimir on 29.11.23.
//

#include "Multithreading_queue.h"

void Multithreading_queue::Run() {
    while(!quite) {
        std::unique_lock<std::mutex> lock(q_mtx);
        q_cv.wait(lock, [this]()->bool{ return !queue_.empty() || quite;});
        if(!queue_.empty()) {
            auto elem = std::move(queue_.front());
            queue_.pop();
            lock.unlock();
            elem.first.get();
            std::lock_guard<std::mutex> lock_g(completed_task_ids_mtx);
            completed_task_ids.insert(elem.second);
            completed_task_ids_cv.notify_all();
        }
    }
}
