#pragma once
#include <tuple>
#include "execution_context/job.h"

namespace execution_context
{
    using job_t = job::data;

    struct sync_t;
    void initialize(sync_t&);
    void cleanup(sync_t&);
    void dispatch(sync_t, job_t);
    struct sync_t:
        public std::tuple<>
    {
    };

}
