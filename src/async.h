#pragma once
#include <mutex>
#include <future>

namespace locks {
    using guard = std::lock_guard<std::mutex>;

    inline guard block(std::mutex& mutex) {
        return guard { mutex };
    }

    inline guard adopt(std::mutex& mutex) {
        return guard { mutex, std::adopt_lock };
    }
}

namespace async {
    template <
        typename T
        >
    bool is_ready(std::future<T> const& f) {
        return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    }
}
