#include <functional>
#include <iostream>
#include <memory>
#include <optional>

#include "execution_context.h"
#include "joblet.h"
#include "static_assert.h"
#include "dbg.h"
#include "test::Test.h"
#include "test::spy.h"
#include "test_runner.h"

#include "spec_execution_context.h"

using std::function;
using std::bind;
using std::optional;
using std::is_default_constructible_v;
using std::array;
using std::ref;


namespace tests {
    test::Test<spec_ec> ec { "test_ec" };
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
