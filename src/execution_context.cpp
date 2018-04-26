#include "execution_context.h"

namespace execution_context
{

void eval_(initialize_t)
{
}


void eval_(cleanup_t)
{
}

void eval_(dispatch_t command)
{
    job_t& j = std::get<1>(command.as_base());
    func(j)();
}

}
