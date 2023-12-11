//
// Created by vladimir on 11.12.23.
//

#pragma once
#include <any>
#include <cassert>
#include <functional>
#include <type_traits>


class Task {
public:
    template<typename FuncRetType, typename ...Args, typename  ...FuncTypes>
    Task(FuncRetType(*func)(FuncTypes...), Args&&... args):
    is_void{std::is_void_v<FuncRetType>} {
        if constexpr (std::is_void_v<FuncRetType>) {
            void_func = std::bind(func, args...);
            any_func = []()->int{return 0;};
        }
        else {
            void_func = []()->void{};
            any_func = std::bind(func, args...);
        }
    }

    void operator()() {
        void_func();
        any_func_result = any_func();
    }

    bool has_result() {
        return !is_void;
    }

    std::any get_result() const {
        assert(!is_void);
        assert(any_func_result.has_value());
        return any_func_result;
    }

private:
    std::function<void()> void_func;
    std::function<std::any()> any_func;
    std::any any_func_result;
    bool is_void;
};

enum class TaskStatus {
    in_q,
    completed
};

struct TaskInfo {
    TaskStatus status = TaskStatus::in_q;
    std::any result;
};