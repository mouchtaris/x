#pragma once
#include "async/lockable.h"
#include "async/signal.h"
#include <vector>

namespace async
{
    template <typename T>
    struct stream:
        public lockable
    {
        std::vector<T>              queue       ;
        signal                      signal_     ;

        template <typename ...Args>
        void                        push(Args&&... args)    ;
        void                        close()                 ;
        std::optional<T>            pull()                  ;

      private:
        T __dequeue() &
        {
            auto&& lock = __lock();
            T result { std::move(queue.back()) };
            queue.pop_back();
            return result;
        }
    };
}
