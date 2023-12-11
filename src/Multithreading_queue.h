//
// Created by vladimir on 29.11.23.
//

#pragma once
#include <algorithm>
#include <future>
#include <mutex>
#include <queue>
#include <unordered_map>
#include "Task.h"

class Multithreading_queue {
public:
    Multithreading_queue(uint32_t num_threads) {
        threads_.reserve(num_threads);
        for(uint32_t i =0; i <num_threads; ++i) {
            threads_.emplace_back(&Multithreading_queue::Run, this);
        }
    }

    template <typename Func, typename ...Args>
    int64_t add_task(const Func& task_funk, Args&&... args) {
        int64_t task_idx = last_idx++;
        std::lock_guard<std::mutex> q_lock(q_mtx);
        queue_.emplace(std::async(std::launch::deferred, task_funk, args...), task_idx);
        q_cv.notify_one();
        return task_idx;
    }

    void wait(int64_t task_id) {
        std::unique_lock<std::mutex> lock(task_info_mtx);
        task_info_cv.wait(lock, [this, task_id]()->bool {
            return task_id < last_idx && task_info[task_id].status != TaskStatus::completed;
        });
    }

    std::any wait_result(const uint64_t task_id) {
        wait(task_id);
        return task_info[task_id].result;
    }

    template<typename T>
    void wait_result(const uint64_t task_id, T& value) {
        wait(task_id);
        value =  std::any_cast<T>(task_info[task_id].result);
    }
    void wait_all() {
        std::unique_lock<std::mutex> lock(task_info_mtx);
        wait_all_cv.wait(lock, [this]()->bool {
            return cnt_completed_tasks == last_idx;
        });
    }

    bool calculated(int64_t task_id) {
        std::lock_guard<std::mutex> lock(task_info_mtx);
        return task_id < last_idx && task_info[task_id].status == TaskStatus::completed;
    }

    ~Multithreading_queue() {
        quite = true;
        q_cv.notify_all();
        for (auto& thread: threads_) {
            thread.join();
        }
    }

private:
    void Run();

    std::queue<std::pair<Task,int64_t>> queue_;
    std::mutex q_mtx;
    std::condition_variable q_cv;

    std::unordered_map<int64_t, TaskInfo> task_info;
    std::condition_variable task_info_cv;
    std::mutex task_info_mtx;

    std::condition_variable wait_all_cv;

    std::vector<std::thread> threads_;
    std::atomic<bool> quite{false};
    std::atomic<int64_t> last_idx{0};
    std::atomic<uint64_t> cnt_completed_tasks{0};
};
