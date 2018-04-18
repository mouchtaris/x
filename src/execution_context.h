#pragma once
#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>
#include "joblet.h"
#include "static_assert.h"
#include "dbg.h"
#include "dbtostr.h"

namespace execution_context {

    struct data {
        using buffer_t = std::vector<joblet>;

        buffer_t front, back;
        bool flipped;
    };

    inline void flip(data& d) {
        d.flipped = !d.flipped;
    }

    inline data::buffer_t& back(data& d) {
        return d.flipped? d.front : d.back;
    }

    inline data::buffer_t const& back(data const& d) {
        return d.flipped? d.front : d.back;
    }

    inline data::buffer_t& front(data& d) {
        return d.flipped? d.back : d.front;
    }

    inline bool enqueue(data& d, std::function<void()> f) {
        front(d).emplace_back( joblet { std::move(f) });
        return true;
    }

    inline bool has_pending(data const& d) {
        return !back(d).empty();
    }

    inline void run_all(data& d) {
        dblog("running all");
        do {
            dblog("flipping");
            flip(d);
            auto& buf = back(d);
            const auto i = begin(buf);
            const auto j = end(buf);
            const auto f = std::mem_fun_ref(&joblet::operator ());
            dblog("foreaching");
            std::for_each(i, j, f);
            dblog(has_pending(d)? "has pending" : "does not has pending");
            dblog(dbtostr(front(d).size()).c_str());
            dblog(dbtostr(back(d).size()).c_str());
        } while (has_pending(d));
    }

}
