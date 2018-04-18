#include "execution_context.h"

#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>

#include "static_assert.h"
#include "dbg.h"
#include "dbtostr.h"

namespace execution_context {

    namespace {
        void flip(data& d) {
            d.flipped = !d.flipped;
        }

        data::buffer_t& back(data& d) {
            return d.flipped? d.front : d.back;
        }

        data::buffer_t& front(data& d) {
            return d.flipped? d.back : d.front;
        }

        data::buffer_t const& front(data const& d) {
            return d.flipped? d.back : d.front;
        }

        bool has_enqueued(data const& d) {
            return !front(d).empty();
        }
    }

    bool enqueue(data& d, std::function<void()> f) {
        auto& buf = front(d);
        buf.emplace_back( joblet { std::move(f) });
        return true;
    }

    void run_all(data& d) {
        do {
            flip(d);
            auto& buf = back(d);
            const auto i = begin(buf);
            const auto j = end(buf);
            const auto f = std::mem_fun_ref(&joblet::operator ());
            std::for_each(i, j, f);
            buf.clear();
        } while (has_enqueued(d));
    }

}
