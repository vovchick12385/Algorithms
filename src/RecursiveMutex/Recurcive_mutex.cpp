//
// Created by vladimir on 17.01.24.
//

#include "Recurcive_mutex.h"
#include <exception>

Recursive_mutex::Recursive_mutex() {
    count_lock =0;
    thread_id = std::this_thread::get_id();//dont know
}

Recursive_mutex::~Recursive_mutex() {
    count_lock--;

}

void Recursive_mutex::lock() {
    if(std::this_thread::get_id()!= thread_id)
        throw std::runtime_error("try to lock locked mutex");
    if(!count_lock)
        mute.lock();
    count_lock++;
}

bool Recursive_mutex::try_lock() {
    if(std::this_thread::get_id() != thread_id)
        return false;
    if(count_lock) {
        if (mute.try_lock()) {
            count_lock++;
            return true;
        } else
            return false;
    }
    count_lock++;
    return true;
}

void Recursive_mutex::unlock() {
    if(std::this_thread::get_id() != thread_id)
        throw std::runtime_error("try to unlock mute in the not current thread");
    count_lock--;
    if(count_lock <=0)
        mute.unlock();
}
