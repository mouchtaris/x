#pragma once
#include <string>
#include <tuple>
#include "test/spy.h"
#include "execution_context.h"
namespace execution_context_spec
{
    using name_t = std::string;
    using direct_spy_base_t = test::spy;
    using indirect_spy_base_t = test::spy;

    struct direct_spy_t:
        public direct_spy_base_t
    {
        using direct_spy_base_t::spy;
    };

    struct indirect_spy_t:
        public indirect_spy_base_t
    {
        using indirect_spy_base_t::spy;
    };

    using data_base_t = std::tuple<
        direct_spy_t,
        indirect_spy_t,
        execution_context::sync_t,
        name_t
        >;
    constexpr size_t    direct_spy_i = 0,
                        indirect_spy_i = 1,
                        sync_ec_i = 2,
                        name_i = 3;
    struct data:
        public data_base_t
    {
    };

    inline data_base_t& as_tuple(data& d) { return d; }

    inline direct_spy_t& direct_spy(data& d) { return std::get<direct_spy_i>(as_tuple(d)); }
    inline indirect_spy_t& indirect_spy(data& d) { return std::get<indirect_spy_i>(as_tuple(d)); }
    inline execution_context::sync_t& sync_ec(data& d) { return std::get<sync_ec_i>(as_tuple(d)); }
    inline std::string& name(data& d) { return std::get<name_i>(as_tuple(d)); }

    void initialize(data&);
    void setup(data&);
    void run(data&);
    bool check(data);
    void cleanup(data&);
}
