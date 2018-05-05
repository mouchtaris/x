#pragma once
#include "async/stream.h"
#include "async/signal.hpp"

namespace async
{
    template <typename T>
    template <typename ...Args>
    void stream<T>::push(Args&&... args)
    {
        auto&& lock = __lock();
        queue.emplace_back(std::forward<Args>(args)...);
        signal_();
    }

    template <typename T>
    void stream<T>::close()
    {
        signal_.close();
    }

    template <typename T>
    std::optional<T> stream<T>::pull()
    {
        signal::wait_t&& sigopt = signal_.wait();
        if (sigopt.has_value())
            return __dequeue();
        return std::nullopt;
    }
}
