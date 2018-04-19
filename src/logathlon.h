#pragma once
#ifndef NDEBUG
#include <sstream>

void __log_impl(char const* const name);

struct __trace_impl {
    char const* const name;

    template <typename ...Args>
    void operator () (Args&&... args) {
        std::ostringstream os;
        (void) (
            (
                (os << "LOG[" << name << "]: ")
                << ...
                << std::forward<Args>(args)
            )
        );
        __log_impl(os.str().c_str());
    }
};

#define log(wat) inline void wat(...) { __log_impl(#wat); }
#define TRACE __trace_impl { __PRETTY_FUNCTION__ }

namespace job_dispatcher {
struct data;
}

namespace logathlon {
    namespace log {
        namespace job_dispatcher {
            // log(initialize)
            // log(cleanup)
            // log(run)
            // log(enqueue)
            // log(cleanup_running)
            // log(cleanup_a_running)
            // log(dispatch_next)
            // log(dispatch_enqueued)
        }
    }
}
#else
namespace logathlon {
}
#endif
