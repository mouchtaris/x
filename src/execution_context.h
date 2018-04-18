#pragma once
#include <vector>
#include "joblet.h"

namespace execution_context {

    struct data {
        using buffer_t = std::vector<joblet>;

        data() = default;
        data(data const&()) = delete;

        buffer_t front, back;
        bool flipped = false;
    };

    bool enqueue(data& d, std::function<void()> f);
    void run_all(data& d);

}
