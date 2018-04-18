#pragma once

#ifndef NDEBUG
#   include <sstream>
#   define                              \
        dbtostr(v)                      \
            dbtostr::tostr((v))
namespace dbtostr {
    template <typename T>
    std::string tostr(T&& t) {
        std::ostringstream o;
        o << t;
        o.flush();
        return o.str();
    }
}
#else
#   include "static_assert.h"
#   define                              \
        dbtostr(v)                      \
            STATIC_ASSERT(false)
#endif
