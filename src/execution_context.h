#pragma once
#include "job_dispatcher.h"

namespace execution_context {

    struct data:
        public job_dispatcher::data
    { };

    void initialize(data& d);
    void finalize(data& d);
    void run_all(data& d);

    bool enqueue(data& d, std::function<void()> f);

}
