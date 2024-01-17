#include <iostream>
#include "HierarchicalMutex/Hierarchical_mutex.h"


thread_local int Hierarchical_mutex::thread_level = 0;

Hierarchical_mutex mute0(10);
Hierarchical_mutex mute1(20);


void WorkMute1(){
    std::lock_guard<Hierarchical_mutex> H_lock(mute0);
}

void WorkMute2(){
    std::lock_guard<Hierarchical_mutex> H_lock2(mute1);
}

void Work(){
    std::lock_guard<Hierarchical_mutex> H_lock1(mute0);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    WorkMute2();
}

void Work2(){
    std::lock_guard<Hierarchical_mutex> H_lock2(mute1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    WorkMute1();
}
using namespace std;


int main(){
    std::thread t1(Work);
    std::thread t2(Work2);

    t1.join();
    t2.join();
    return 0;
}
