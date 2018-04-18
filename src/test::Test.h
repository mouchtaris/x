#pragma once
#include <string>
#include <optional>
#include <type_traits>
#include "static_assert.h"

namespace test {
    struct prepare_tag_t { } prepare_tag;
    struct exec_tag_t { } exec_tag;
    struct is_success_tag_t { } is_success_tag;

    template <typename S>
    struct Test {
        STATIC_ASSERT(std::is_default_constructible_v<S>);
        STATIC_ASSERT((std::is_invocable_r_v<bool, S, prepare_tag_t>));
        STATIC_ASSERT((std::is_invocable_r_v<bool, S, exec_tag_t>));
        STATIC_ASSERT((std::is_invocable_r_v<bool, S, is_success_tag_t>));

        std::string name;
        std::optional<S> data_holder { };
        bool is_run { false };
        bool is_success { false };

      public:
        bool success() const { return is_run && is_success; }
        void setup() { data_holder.emplace(); }
        void cleanup() { data_holder.reset(); }
        void run() {
            if (is_run)
                return;
            is_run = true;

            setup();
            auto& data = data_holder.value();
            data(prepare_tag);
            data(exec_tag);
            is_success = data(is_success_tag);
            cleanup();
        }
    };
}
