#pragma once
#include "async/__common.h"
#include "async/ec/task_channel.h"

namespace async::ec::threadpool
{
    struct worker
    {
        TAGGED_VALUE(id, std::uint32_t);
        using rec = record<worker, id, task_channel>;

        static void do_work(rec data)
        {
            channel<task::rec>&         taskchan = tagged_value::get(gett<task_channel>(data));
            std::optional<task::rec>    next_task_opt;
            const auto                  get_next_task = [&next_task_opt, &taskchan] ()
                                        {
                                            next_task_opt = std::move(taskchan.pull());
                                            return next_task_opt.has_value();
                                        };
            while (get_next_task())
                get(gett<job>(next_task_opt.value()))();
        };

        static rec make(id::value_t _id_val, channel<task::rec>& tasks)
        {
            using tagged_value::    make;
            using std::             move;
            auto&& _id              = make<id>(_id_val);
            auto&& taskchan         = make<task_channel>(std::ref(tasks));
            auto&& workr            = make_record<worker>(move(_id), move(taskchan));
            return move(workr);
        }
    };

}
