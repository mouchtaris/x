#include <functional>
#include <iostream>
#include <memory>
#include <optional>

#include "execution_context.h"
#include "static_assert.h"
#include "dbg.h"
#include "test::Test.h"
#include "test::spy.h"
#include "test_runner.h"
#include "async.h"

#include "execution_context_spec.h"

using std::function;
using std::bind;
using std::optional;
using std::is_default_constructible_v;
using std::array;
using std::ref;

namespace promise {
    template <typename R>
    struct data {
        std::optional<R> value_opt;
        std::mutex value_mutex;
        std::vector<std::function<void(R)>> on_complete;
        std::mutex on_complete_mutex;
    };

    template <
        typename R,
        typename U
        >
    void complete(data<R>& d, U&& v) {
        const auto lock = locks::block(d.value_mutex);
        d.value_opt = std::forward<U>(v);
    }
}


namespace tests {
    test::Test<execution_context_spec> ec { "test_ec" };
}

void run_all_tests() {
    run_test(tests::ec);
}


const auto println = [](auto&& w) -> decltype(auto) { return std::cout << w << '\n'; };
template <typename T> void pig(T) { println(__PRETTY_FUNCTION__); }
int main(int, char**)
{
    run_all_tests();
    std::cout.flush();
    std::cerr.flush();
    return 0;
}
