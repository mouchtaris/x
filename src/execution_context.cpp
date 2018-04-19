#include "execution_context.h"

namespace execution_context {

    namespace {
    }

    void initialize(data& d) {
        job_dispatcher::data::initialize(d);
    }

    void finalize(data& d) {
        job_dispatcher::data::cleanup(d);
    }

    bool enqueue(data& d, std::function<void()> f) {
        d.run(move(f));
        return true;
    }

    void run_all(data&) {
    }

}
