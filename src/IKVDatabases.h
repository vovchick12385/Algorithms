//
// Created by vladimir on 24.11.23.
//

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <string_view>

struct IKVDatabase{
    virtual std::string get(std::string_view key) = 0;
    virtual std::vector<std::string> all_keys() = 0;
    virtual ~IKVDatabase() = default;
};

// shared_mutex (use it here)
// conditional_variable (spurious wakeup)
// timed_mutex (try to use it)
// recursive_mutex (only read it)

// joinable() - method


// thread pool


struct IKWrapper: IKVDatabase{

    IKWrapper(){
        t = std::thread((std::bind(&IKWrapper::update, this)));

    }
    ~IKWrapper(){
        is_end = true;
        notifier.notify_one();
        t.join();
    }

    virtual std::string get(std::string_view key) override{
        std::string out;
        wrap_mute.lock_shared();
        const auto& it = cache.find(key.data());
        if(it != end(cache))
            wrap_mute.unlock_shared();
            return it->second;
        wrap_mute.unlock_shared();

        out = IKVDatabase::get(key);

        wrap_mute.lock_shared();
        cache[key.data()] = out;
        wrap_mute.unlock_shared();
        return out;
    }
    virtual std::vector<std::string> all_keys() override{

        return IKVDatabase::all_keys();
    }

private:
    void update(){
        while(!is_end){
            std::unique_lock<std::shared_mutex> lock(wrap_mute);
            using namespace std::chrono_literals;
            if (!notifier.wait_for(lock, 1min, [=]{ return is_end.load(); }))
                return;
            //
            lock.unlock();
            std::unordered_map<std::string, std::string> temp;
            auto keys = IKVDatabase::all_keys();
            for(const auto& key: keys){
                if(is_end)
                    return;
                temp[key] = IKVDatabase::get(key);
            }
            lock.lock();
            //wrap_mute.lock();
            cache.swap(temp);
            //wrap_mute.unlock;

        }
    }
    std::condition_variable_any notifier;
    std::atomic<bool> is_end;
    std::shared_mutex wrap_mute;
    std::thread t;
    std::unordered_map<string, string> cache;
};