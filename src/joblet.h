#pragma once

#include <functional>

struct joblet {
    std::function<void ()> task;
    inline void run() { task(); }
    inline void operator () () { run(); }
};
