#pragma once
#include <tuple>
#include <functional>
#include <vector>
#include <mutex>
#include <future>

namespace job_dispatcher {
    using std::get;

    namespace joblet {
        using                       name_t = std::string;
        using                       func_t = std::function<void()>;
        using                       data = std::tuple<name_t, func_t>;
        inline name_t&              name(data& d) { return get<0>(d); }
        inline func_t&              func(data& d) { return get<1>(d); }
    }
    using                           joblet_t = joblet::data;

    namespace job {
        using                       fut_t = std::future<void>;
        using                       data = std::tuple<joblet_t, std::future<void>>;
        inline joblet_t&            joblet(data& d) { return get<0>(d); }
        inline fut_t&               future(data& d) { return get<1>(d); }
    }
    using                           job_t = job::data;

    struct data {
        static constexpr auto MAX_JOBS = 4;
        std::vector<job_t>          running;
        std::mutex                  running_mutex;
        std::vector<joblet_t>       pending;
        std::mutex                  pending_mutex;

        static void initialize(data&);
        static void cleanup(data&);

        void run(std::function<void()>);
    };

}
