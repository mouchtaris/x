#include "eval.h"
#include <mutex>

namespace
{
    std::mutex mutex;
}

void on_eval(char const* name)
{
    std::lock_
}
