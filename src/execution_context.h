#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <type_traits>
#include "static_assert.h"
#include "joblet.h"

namespace execution_context {

    struct data {
        using buffer_t = std::vector<joblet>;

        buffer_t front, back;
        bool flipped;
    };

    inline void flip(data& d) {
        d.flipped = !d.flipped;
    }

    inline data::buffer_t const& back(data const& d) {
        return d.flipped? d.front : d.back;
    }

    inline data::buffer_t& front(data& d) {
        return d.flipped? d.back : d.front;
    }

    inline bool enqueue(data& d, joblet j) {
        front(d).emplace_back(std::move(j));
        return true;
    }

    inline bool has_pending(data const& d) {
        return !back(d).empty();
    }

    inline void run_all(data& d) {
        while (has_pending(d)) {
            flip(d);
            const auto i = begin(back(d));
            const auto j = end(back(d));
            const auto f = std::mem_fun_ref(&joblet::operator ());
            std::for_each(i, j, f);
        }
    }

}
