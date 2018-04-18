#pragma once

#ifndef NDEBUG
#   define                          \
        debug_enabled               \
            true
#   define                          \
        dblog(msg)                  \
            debug::log((msg))
namespace debug {
    void log(char const* msg);
}
#else
#   define                          \
        dblog(msg)
#endif
