#pragma once
#include <mutex>

namespace async
{
    struct lockable
    {
        using lock_t = std::unique_lock<std::mutex>;
        std::mutex mutex { };

        lock_t __lock() &
        {
            return lock_t { mutex };
        }
    };

}
