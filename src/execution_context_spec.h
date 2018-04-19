#pragma once
#include <array>
#include <functional>
#include <utility>
#include <optional>
#include "execution_context.h"
#include "test::spy.h"
#include "test::Test.h"

struct execution_context_spec {
    std::optional<execution_context::data>  ec_opt;
    std::array<test::spy, 3>                spies { { { "a" }, { "b" }, { "c" } } };
    test::spy                               recspy { "recspy" };
    //
    execution_context::data&                ec()                        { return ec_opt.value(); }
    //
    const std::function<void (test::spy&)>  tickle                      = std::mem_fn(&test::spy::operator ());
    std::function<void()>                   close_tickle(test::spy& s)  { return bind(tickle, std::ref(s)); }
    const std::function<void (test::spy&)>  enqueue_tickle              = [this] (test::spy& s) { enqueue(ec(), close_tickle(s)); };
    //
    const std::function<void()>             recjob                      = std::bind(enqueue_tickle, std::ref(recspy));
    const std::function<void()>             enqueue_recjob              = [this] () { enqueue(ec(), recjob); };


    void _init() {
        ec_opt.emplace();
        initialize(ec());
    }

    void _cleanup() {
        finalize(ec());
        ec_opt.reset();
    }

    bool operator () (test::prepare_tag_t) {
        _init();
        for_each(begin(spies), end(spies), enqueue_tickle);
        enqueue_recjob();
        return true;
    }

    bool operator () (test::exec_tag_t) {
        run_all(ec());
        _cleanup();
        return true;
    }

    bool operator() (test::is_success_tag_t) {
        return
            std::all_of(
                begin(spies),
                end(spies),
                std::mem_fn(&test::spy::called)
            )
            && recspy.called
        ;
    }
};
