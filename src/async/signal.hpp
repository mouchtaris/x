#pragma once
#include "async/signal.h"

namespace async
{
    inline void signal::__notify_one(lock_t& lock) &
    {
        lock.unlock();
        cond.notify_one();
    }

    inline void signal::__notify_all(lock_t& lock) &
    {
        lock.unlock();
        cond.notify_all();
    }

    inline void signal::__wait(lock_t& lock) &
    {
        cond.wait(lock, __should_activate);
    }

    inline signal::wait_t signal::wait() &
    {
        while (true) {
            auto&& lock = __lock();
            if (waiting > 0) {
                --waiting;
                return std::nullptr_t { };
            }
            if (closed)
                return std::nullopt;
            __wait(lock);
        }
    }

    inline void signal::operator()() &
    {
        auto&& lock = __lock();
        if (closed)
            return;
        ++waiting;
        __notify_one(lock);
    }

    inline void signal::close() &
    {
        auto&& lock = __lock();
        closed = true;
        __notify_all(lock);
    }
}
