#pragma once
#include "test::Test.h"
#include "dbg.h"
template <typename S>
void run_test(test::Test<S>& test) {
    test.run();
    dblog((
        std::string("Running test ") +
        test.name +
        ": " +
        (test.success()? "success" : "FAILURE")
    ).c_str());
}
