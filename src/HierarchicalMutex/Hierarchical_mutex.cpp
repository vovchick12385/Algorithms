//
// Created by vladimir on 17.01.24.
//

#include "Hierarchical_mutex.h"

Hierarchical_mutex::Hierarchical_mutex(int l) {
    previous_level = 0;
    level = l;
}

void Hierarchical_mutex::lock() {
    if(!checkLockValid())
        throw std::runtime_error("current level is locked");
    mute.lock();
    updateLevels();
}

void Hierarchical_mutex::unlock() {
    thread_level = previous_level;
    mute.unlock();
}

bool Hierarchical_mutex::tryLock() {
    if(!checkLockValid() || !mute.try_lock())
        return false;
    updateLevels();
    return true;
}

bool Hierarchical_mutex::checkLockValid() const{
    if(thread_level<= level)
        return false;
    return true;
}

void Hierarchical_mutex::updateLevels() {
    previous_level = thread_level;
    thread_level = level;
}
