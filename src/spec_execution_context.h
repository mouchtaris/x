#pragma once
#include <array>
#include <functional>
#include <utility>
#include "execution_context.h"
#include "test::spy.h"
#include "test::Test.h"

struct spec_ec {
    execution_context::data ec;
    std::array<test::spy, 3> spies;

    bool operator () (test::prepare_tag_t) {
        auto f = std::mem_fn(&test::spy::operator ());
        for (auto& s: spies) {
            auto job = bind(f, std::ref(s));
            enqueue(ec, move(job));
        }
        return true;
    }

    bool operator () (test::exec_tag_t) {
        run_all(ec);
        return true;
    }

    bool operator() (test::is_success_tag_t) {
        return std::all_of(
            begin(spies),
            end(spies),
            std::mem_fn(&test::spy::called)
        );
    }
};
