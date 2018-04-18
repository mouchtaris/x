#include <functional>
#include <iostream>
#include <memory>

#include "execution_context.h"
#include "joblet.h"
#include "static_assert.h"

using std::function;

const auto println = [](auto&& w) -> decltype(auto) { return std::cout << w << '\n'; };
template <typename T> void pig(T) { println(__PRETTY_FUNCTION__); }
int main(int, char**)
{
    execution_context::data ec;
    enqueue(ec, std::bind(println, "Hello"));
    enqueue(ec, std::bind(println, "this is the end"));
    run_all(ec);
    std::cout.flush();
    std::cerr.flush();
    return 0;
}
