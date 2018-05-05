#pragma once
#include "async/lockable.h"
#include "async/signal.h"
#include "async/channel.h"

#include "make_array.h"
#include "record.h"
#include "s.h"

#include <thread>
#include <functional>

namespace async
{
    namespace ec
    {
        TAGGED_VALUE(job, std::function<void()>);

        struct task
        {
            TAGGED_VALUE(name, std::string);
            using rec = record<task, name, job>;
        };

        namespace threadpool
        {
            TAGGED_VALUE(task_channel, std::reference_wrapper<channel<task::rec>>);

            struct worker
            {
                TAGGED_VALUE(id, std::uint32_t);
                using rec = record<worker, id, task_channel>;

                static constexpr auto f = [](rec data)
                {
                    task_channel _task_channel = gett<task_channel>(data);
                    std::reference_wrapper<channel<task::rec>> _task_channel_ref = get(_task_channel);
                    channel<task::rec>& taskchan = _task_channel_ref;
                    std::optional<task::rec> next_task_opt;
                    const auto get_next_task = [&next_task_opt, &taskchan] () {
                        next_task_opt = std::move(taskchan.pull());
                        return next_task_opt.has_value();
                    };
                    while (get_next_task()) {
                        task::rec& task = next_task_opt.value();
                        get(gett<job>(task))();
                    }
                };
            };

            static worker::rec make_worker(std::uint32_t _id, channel<task::rec>& tasks)
            {
                using tagged_value::make;
                return make_record<worker>(
                    make<worker::id>(_id),
                    make<task_channel>(std::ref(tasks))
                );
            }

            template <size_t size>
            struct data
            {
                channel<task::rec>              task_channel { };
                std::array<std::thread, size>   threads {
                    make_array<size>(
                        [this](uint32_t _id) {
                            return std::thread {
                                worker::f,
                                make_worker(_id, task_channel)
                            };
                        }
                    )
                };
            };

            template <size_t size>
            using data_t = data<size>;

            template <size_t size>
            auto make()
            {
                return data_t<size> { };
            }

            template <size_t size>
            void cleanup(data_t<size>& data)
            {
                for (auto& thread: data.threads)
                    thread.join();
            }
        }

        // template <size_t size>
        // struct threadpooll
        // {
        //     using threads_t = std::array<std::thread, size>;
        //     using task_t = std::function<void()>;
        //     using stream_t = stream<task_t>;

        //     static std::thread create_worker_thread(std::size_t id)
        //     {
        //         return { };
        //     }

        //     stream_t s;
        //     threads_t threads {
        //         make_array<size>(&create_worker_thread)
        //     };
        // };
    }
}
