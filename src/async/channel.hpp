#pragma once
#include "async/channel.h"
#include "async/signal.hpp"

namespace async
{
    template <typename T>
    template <typename ...Args>
    void channel<T>::push(Args&&... args)
    {
        auto&& lock = __lock();
        queue.emplace_back(std::forward<Args>(args)...);
        signal_();
    }

    template <typename T>
    void channel<T>::close()
    {
        signal_.close();
    }

    template <typename T>
    std::optional<T> channel<T>::pull()
    {
        signal::wait_t&& sigopt = signal_.wait();
        if (sigopt.has_value())
            return __dequeue();
        return std::nullopt;
    }
}
