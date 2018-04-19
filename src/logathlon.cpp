#include "logathlon.h"
#include <iostream>
#include <mutex>

namespace {
    std::mutex mutex;
}

void __log_impl(char const* const name) {
    std::lock_guard<std::mutex> lock { mutex };
    std::cerr << "LOG:" << name << '\n';
}
