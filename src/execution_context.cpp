#include "execution_context.h"

namespace execution_context
{

void initialize(sync_t&)
{
}

void cleanup(sync_t&)
{
}

void dispatch(sync_t, job_t j)
{
    func(j)();
}

}
