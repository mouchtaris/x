#pragma once
#include "async/lockable.h"
#include "async/signal.h"
#include <vector>

namespace async
{
    template <typename T>
    struct channel:
        public lockable
    {
        using                       value_t = T ;
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

    template <typename _Chan>
    struct channel_iterator
    {
        using channel_t     = _Chan;
        using value_t       = typename channel_t::value_t;
        using parent_t      = std::reference_wrapper<channel_t>;
        using value_opt_t   = std::optional<value_t>;

        parent_t            _parent;
        value_opt_t         _value_opt;

        bool                is_end() const& { return !_value_opt.has_value(); }

        bool                operator !=(channel_iterator<channel_t> const& other) const&
                            {
                                return is_end() != other.is_end();
                            }
        void                operator ++() &
                            {
                                _value_opt = _parent.get().pull();
                            }
        value_t             operator *() const&
                            {
                                return _value_opt.value();
                            }
    };

    template <typename T>
    auto begin(channel<T>& chan)
    {
        return channel_iterator<channel<T>> { std::ref(chan), chan.pull() };
    }

    template <typename T>
    auto end(channel<T>& chan)
    { 
        return channel_iterator<channel<T>> { std::ref(chan), std::nullopt };
    }
}
