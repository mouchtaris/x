#ifndef __ASYNC__LOCKABLE_H__
#define __ASYNC__LOCKABLE_H__
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
#endif // __ASYNC__LOCKABLE_H__
