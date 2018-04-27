#include "eval.h"
#include <mutex>
#include <iostream>

namespace
{
    std::mutex mutex;
}

void on_eval(char const* name)
{
    std::lock_guard<std::mutex> lock { mutex };
    std::cerr << name << '\n';
}
