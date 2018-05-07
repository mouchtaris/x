#pragma once
#include <condition_variable>
#include <optional>
#include <functional>
#include "async/lockable.h"

namespace async
{
    struct signal:
        public lockable
    {
        using                       wait_t  = std::optional<std::nullptr_t>;
        std::size_t                 waiting { 0         };
        std::condition_variable     cond    {           };
        bool                        closed  { false     };

        const std::function<bool()> __should_activate =
            [this]() { return closed || waiting > 0; };

        void __notify_one   (lock_t&    ) &;
        void __notify_all   (lock_t&    ) &;
        void __wait         (lock_t&    ) &;

        wait_t wait         (           ) &;

        void operator()     (           ) &;
        void close          (           ) &;
    };
}
