#pragma once
#include <string>
#include <tuple>
#include <functional>
namespace execution_context::job
{
    using name_t = std::string;
    using func_t = std::function<void()>;

    using data_base_t = std::tuple<name_t, func_t>;
    constexpr size_t    name_i = 0,
                        func_i = 1;
    struct data: public data_base_t
    {
        using data_base_t::tuple;
    };

    inline name_t name(data d) { return std::get<name_i>(d); }
    inline func_t func(data d) { return std::get<func_i>(d); }
}
