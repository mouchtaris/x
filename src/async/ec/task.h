#ifndef __ASYNC__EC__TASK_H__
#define __ASYNC__EC__TASK_H__
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
#endif // __ASYNC__EC__TASK_H__
