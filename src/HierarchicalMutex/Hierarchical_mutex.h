//
// Created by vladimir on 17.01.24.
//

#pragma once
#include <thread>

class Hierarchical_mutex {
public:
    static thread_local int thread_level;

    explicit Hierarchical_mutex(int l);

    void lock();

    void unlock();

    bool tryLock();

private:
    bool checkLockValid() const;

    void updateLevels();

    std::mutex mute;

    int level;
    int previous_level;
};


