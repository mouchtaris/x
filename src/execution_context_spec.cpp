#include "execution_context_spec.h"

namespace execution_context_spec
{

using namespace execution_context;

void initialize(data& d)
{
    name(d) = "Execution Context Spec";
}

void setup(data& d)
{
    initialize(sync_ec(d));
}

void run(data& d)
{
    sync_t& ec = sync_ec(d);

    // Enqueue a job that calls the direct spy
    dispatch(ec, {
        "direct spy calling",
        [&d](){ direct_spy(d)(); }
    });

    // Enqueue a job that calls the indirect spy (indirectly)
    dispatch(ec, {
        "indirect spy calling job",
        [&ec, &d]() {
            dispatch(ec, {
                "indirect spy calling",
                [&d]() { indirect_spy(d)(); }
            });
        }
    });
}

bool check(data d)
{
    return
        direct_spy(d).called &&
        indirect_spy(d).called;
}

}
