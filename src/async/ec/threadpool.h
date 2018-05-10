#ifndef __ASYNC__EC__THREADPOOL_H__
#define __ASYNC__EC__THREADPOOL_H__
#include "async/__common.h"
#include "async/ec/threadpool/worker.h"
#include "make_array.h"
#include <thread>
#include <algorithm>
#include <functional>

namespace async::ec::threadpool
{
    template <
        size_t size
        >
    struct data
    {
        typedef std::array<std::thread, size>       threads_t;
        typedef channel<task::rec>                  task_channel_t;
        //
        typedef std::thread                         __make_thread_func_t(worker::id::value_t);
        typedef std::function<__make_thread_func_t> __make_thread_t;
        //
        //
        // Task channel init is easy.
        channel<task::rec>              task_channel { };
        //
        //
        // Threads on the other hand, not so much...
        const __make_thread_t           __make_thread = [this] (auto _id_val) {
                                            return std::thread {
                                                worker::do_work,
                                                worker::make(std::move(_id_val), task_channel)
                                            };
                                        };
        threads_t                       threads { make_array<size>(__make_thread) };

        void dispatch(task::rec task) { task_channel.push(std::move(task)); }

        ~data()
        {
            terminate();
            cleanup();
        }
    private:
        void terminate() { task_channel.close(); }
        void cleanup() { for (auto& t: threads) if (t.joinable()) t.join(); }
    };

    template <size_t size>
    using data_t = data<size>;

    template <size_t size>
    auto make()
    {
        return data_t<size> { };
    }
}
#endif // __ASYNC__EC__THREADPOOL_H__
