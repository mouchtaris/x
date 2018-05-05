#pragma once
#include "async/__common.h"
#include "async/ec/job.h"

namespace async::ec
{
    struct task
    {
        TAGGED_VALUE(name, std::string);

        using rec = record<task,
              name,
              job
        >;
    };
}
